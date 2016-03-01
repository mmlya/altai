#include "ssim.h"

int main(int argc, char* argv[]){
	
	if(!argv[1]){
		printf("First argument must be the name of the file containing demographic hypothesis!\n");
		//return(-1);
	}
	rinit();
	printf("\n\n\tCurrent vers: %s\n\n", VERSION);
	printf("\n\t\tAssumed scenario for spec.1:\n");
	printf("\tLength\tStart #\t end #\n");
	printf("\t========================\n");
	steps=0;
	if(argv[1]!=NULL) readfate(argv[1]);
	else readfate("ffile");
	printf("\t========================\n");
	printf("Total number of mutation steps: \t%i\n",steps);
	printf("Maximal number of organisms: \t\t%i\n",maxN);
	
	capacity = malloc(steps*sizeof(int));
	capacity1 = malloc(steps*sizeof(int));
	swing12 = malloc(steps*sizeof(float));
	swing21 = malloc(steps*sizeof(float));
	
	if(argv[1]==NULL) ffile=fopen("ffile","r");

	for(i=0;i<steps;i++){
		fgets(buf1,50,ffile);
		sscanf(buf1,"%i %i %i", &j, &capacity[i],&capacity1[i]);
		//capacity[i]=atoi(buf1);
	}
	readM();
	//printf("\n\n=====HERE!======\n\n");
	delta = (double)steps/10.0;

	readparams();
	printf("Number of simulations:\t\t%i\n",param.numRep);
	/*
	delta=(float)maxN/10.0;
	for(i=0;i<10;i++){
		sprintf(buf1,"%6.0f",delta*(float)i);
	}
	*/
	growthCurves = malloc((param.numRep+2)*sizeof(double *));
	distribND = malloc((param.numRep+1)*sizeof(double));
	for(i=0;i<param.numRep;i++) growthCurves[i]=malloc(steps*sizeof(double));
	for(i=0;i<steps;i++) growthCurves[0][i]=capacity[i];
	printf("Length of mitochondrial sequence:\t%i\n", param.nucLength);
	printf("Max possible size of Species 1:\t%i\n",maxN);
	printf("Max possible size of Species 2:\t%i\n",maxN1);
	f3=fopen("rawcurves.dat","w");
	/****** CYCLING ******/
	for(bot=0;bot<param.numRep;bot++){
		fder=malloc(sizeof(gad));
		fder1=malloc(sizeof(gad));
		fd=malloc(sizeof(gad));
		initgad(fder,param.nucLength);
		initgad(fder1,param.nucLength);
		initgad(fd,param.nucLength);
		copygad(fder,fder1);
		copygad(fder,fd);
		//mutations will move apart the founders
		for(i=0;i<MUTSTEPS;i++)  nucMut(fder1);
		for(i=0;i<AMUTSTEPS;i++) aaMut(fder1);
		for(i=0;i<MUTSTEPS;i++)  nucMut(fder);
		for(i=0;i<AMUTSTEPS;i++) aaMut(fder);
		if(bot==0) f1=fopen("demogr.dat","w");
		if(g!=NULL) gsl_histogram_free(g);
		g=gsl_histogram_alloc(param.epyN);
		
		printf("\nStarting organism of spec1:\n");
		for(i=0;i<param.nucLength;i++) printf("%c",nucleotides[fder->nuc[i]]);
		printf("\nStarting organism of spec2:\n");
		for(i=0;i<param.nucLength;i++){
		  if(fder->nuc[i]==fder1->nuc[i]) printf(".");
		  else printf("%c",nucleotides[fder1->nuc[i]]);
		}
		printf("\n");
		G0=malloc(maxN*sizeof(founder));
		G1=malloc(maxN1*sizeof(founder));
		start(fder);
		start1(fder1);
		printf("simulation %i\n", bot+1);
		for(j=0;j<steps;j++){
			num=howmany();
			num1=howmany1();
			//printf("%i\t%i\t%i\n",j, num, num1);
			if(bot==0) fprintf(f1,"%i\t%i\t%i\t%i\t%i\t%4.3f\t%4.3f\n",j,num,capacity[j],num1,capacity1[j],swing12[j],swing21[j]);
			//if(bot)growthCurves[bot][j]=num;
			if(num<10){
				printf("\n\t\tExtinction at step %i in Species 1\n", j);
				//break;
				return(-1);
			}
			if(num1<10){
				printf("\n\t\tExtinction at step %i in Species 2\n", j);
				break;
			}
			//if((j % 10)==0) printf("%i  %i  %i\n",j,num,capacity[j]);
			for(count=0;count<maxN;count++){
				if(G0[count]->willSurvive){
					if(gsl_rng_uniform(r)<param.mutprob1) nucMut(G0[count]);
					if(gsl_rng_uniform(r)<param.mutprob2) aaMut(G0[count]);
				}
			}
			for(count=0;count<maxN1;count++){
				if(G1[count]->willSurvive){
					if(gsl_rng_uniform(r)<param.mutprob1) nucMut(G1[count]);
					if(gsl_rng_uniform(r)<param.mutprob2) aaMut(G1[count]);
				}
			}
			if(gsl_rng_uniform(r)<param.mutprob1) nucMut(fd);
			if(gsl_rng_uniform(r)<param.mutprob2) aaMut(fd);
			if(swing12[j]>0 && swing21[j]>0) swinger(swing12[j],swing21[j],j);
			mate(j);
			survive(j);
			mate1(j);
			survive1(j);
			//if(swing12[j]>0 && swing21[j]>0) swinger(swing12[j],swing21[j],j);
		}
		if(bot==0){
			fclose(f1);
			sampleNuc(40, num);
			sampleNuc1(40,num1);
			sampleAA(40,num);
			sampleAa1(40,num);
		}
		/**/
		distribND[bot]=aver();
		dmax=0;
		/*finds max pairwise distance of species 0*/
		for(x=0;x<maxN-1;x++){
			if(G0[x]->willSurvive){
				for(y=x+1;y<maxN;y++){
					if(G0[x]->willSurvive){
						dts=dst(x,y);
						if(dts>dmax) dmax=dts;
					}
				}
			}
		}
		gsl_histogram_set_ranges_uniform(g,0,dmax);
		for(x=0;x<maxN-1;x++){
			if(G0[x]->willSurvive){
				for(y=x+1;y<maxN;y++){
					if(G0[x]->willSurvive){
						gsl_histogram_increment(g,dst(x,y));
					}
				}
			}
		}
		gsl_histogram_fprintf(f3,g,"%f","%f");
		fprintf(f3,"\n");
		norm=(double)howmany();
		norm=norm*(norm-1.0)/2.0;
		for(x=0;x<param.epyN;x++){
			delta=gsl_histogram_get(g,x)/norm;
		}
		
		printf("%i\tDIVERSITY = %8.5f\n",bot,distribND[bot]);
		/**/
		for(i=0;i<maxN;i++){
			//printf("%i\n",i); 
			free(G0[i]->nuc);
			free(G0[i]->aa1);
			free(G0[i]->aa2);
		}
		free(G0);
		free(fder->nuc);
		free(fder->aa1);
		free(fder->aa2);
		for(i=0;i<maxN1;i++){
			//printf("%i\n",i);
			free(G1[i]->nuc);
			free(G1[i]->aa1);
			free(G1[i]->aa2);
		}
		free(G1);
		free(fder1->nuc);
		free(fder1->aa1);
		free(fder1->aa2);
	}
	/********        cycling off       ************/
	printf("\n\n Umfffff!\n");
	Nmin=1;Nmax=0;
	for(j=0;j<param.numRep;j++){
		if(distribND[j]<Nmin) Nmin=distribND[j];
		if(distribND[j]>Nmax) Nmax=distribND[j];
	}
	
	if(h!=NULL) gsl_histogram_free(h);
	h=gsl_histogram_alloc(20);
	gsl_histogram_set_ranges_uniform(h, 0, Nmax);
	for(i=0;i<param.numRep;i++){
	  gsl_histogram_increment(h,distribND[i]);
	} 
	/**********************************************
	 *    Linux stuff: adaptation for gnuplot     *
	 **********************************************/
	f1=fopen("distrib1.dat","w");
	gsl_histogram_fprintf(f1,h,"%f","%f");
	fclose(f1);
	free(capacity);
	free(capacity1);
	free(swing12);
	free(swing21);
	return(0);
}
