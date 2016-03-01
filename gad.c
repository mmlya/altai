/***************************************************************************
 *   Copyright (C) 2007 by Dmitry   *
 *   dysh@sherb1   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "gad.h"

void initgad(founder fd, int l1){
	int i,j;

	fd->age=0;
	fd->fitness=1.0;
	fd->willSurvive=1;
	fd->nuc = malloc(l1*sizeof(int));
	fd->aa1 = malloc(param.aaLength*sizeof(int));
	fd->aa2 = malloc(param.aaLength*sizeof(int));
	for(j=0;j<param.aaLength;j++){
		fd->aa1[j]=ramino();
		fd->aa2[j]=fd->aa1[j];
	}
	
	for(i=0;i<l1;i++){
		fd->nuc[i]=rnucl();
	}
    return;    
}

void cloneFndr(founder fndr,founder tmp){
	int i;
	if(tmp==NULL){
		tmp = malloc(sizeof(gad));
		tmp->aa1=malloc(param.aaLength*sizeof(int));
		tmp->aa2=malloc(param.aaLength*sizeof(int));
		tmp->nuc=malloc(param.nucLength*sizeof(int));
	}
	tmp->age=0;
	for(i=0;i<param.aaLength;i++){
		tmp->aa1[i]=fndr->aa1[i];
		tmp->aa2[i]=fndr->aa2[i];
	}
//	tmp->nuc = malloc(param.nucLength*sizeof(int));
	for(i=0;i<param.nucLength;i++){
		tmp->nuc[i]=fndr->nuc[i];
	}
	tmp->willSurvive=1;
	tmp->fitness = fndr->fitness;
	return;
}

void growUp(founder g) {
	g->age++;
	if(g->age>param.maxLife) g->willSurvive=0;
	return;
}

void aaMut(founder g) {
	int tmp,tmp1,i;
	
	i = rpos(param.aaLength);
	if(oneoftwo()){
		tmp = g->aa1[i];
		tmp1= tmp;
		for(;tmp1==tmp;) {
			tmp1=ramino();
		} 
		g->aa1[i]=tmp1;
	} else {
		tmp = g->aa2[i];
		tmp1= tmp;
		for(;tmp1==tmp;) {
			tmp1=ramino();
		} 
		g->aa2[i]=tmp1;
	}
	return;
}

void aaMut2(founder g) {
	int tmp,tmp1,i;
	
	i = rpos(param.aaLength);
	tmp = g->aa1[i];
	tmp1= tmp;
	for(;tmp1==tmp;) {
		tmp1=ramino();
	} 
	g->aa1[i]=tmp1;
	g->aa2[i]=tmp1;
	return;
}
void nucMut(founder g) {
	int tmp, tmp1,i,j;
	
	j = param.nucLength;
	i = rpos(j);
	tmp = g->nuc[i];
	tmp1 = tmp;
	for(;tmp==tmp1;){
		tmp1 = rnucl();
	}
	g->nuc[i]=tmp1;
	return;
}

void killTvar(founder tv){
	
	free(tv->nuc);
	free(tv);
	return;
	
}

void copygad(founder src, founder target){
	int i;
	
	target->age=src->age;
	target->willSurvive = src->willSurvive;
	target->fitness = src->fitness;
	
	for(i=0;i<param.nucLength;i++) target->nuc[i]=src->nuc[i];
	for(i=0;i<param.aaLength;i++){
		target->aa1[i]=src->aa1[i];
		target->aa2[i]=src->aa2[i];
	}
	return;
}

void start(founder f){
	int i, size;
	
	size = maxN;
	for(i=0;i<size;i++){
		G0[i]=malloc(sizeof(gad));
		G0[i]->aa1=malloc(param.aaLength*sizeof(int));
		G0[i]->aa2=malloc(param.aaLength*sizeof(int));
		G0[i]->nuc=malloc(param.nucLength*sizeof(int));
		G0[i]->willSurvive=0;
		if(i<startN) {
			cloneFndr(f,G0[i]);
			G0[i]->willSurvive=1;
		}
	}
	/* fitness not yet cloned*/		
	return;
}

void start1(founder f){
	int i, size;
	
	size = maxN1;
	printf("%i\n", maxN1);
	for(i=0;i<maxN1;i++){
		G1[i]=malloc(sizeof(gad));
		G1[i]->aa1=malloc(param.aaLength*sizeof(int));
		G1[i]->aa2=malloc(param.aaLength*sizeof(int));
		G1[i]->nuc=malloc(param.nucLength*sizeof(int));
		G1[i]->willSurvive=0;
		if(i<startN) {
			cloneFndr(f,G1[i]);
			G1[i]->willSurvive=1;
		}
	}
	/* fitness not yet cloned*/		
	return;
}

int howmany(){
	int n,i;
	
	n=0;
	for(i=0;i<maxN;i++){
		if(G0[i]==NULL){
			printf("\nmemory leak at i=%i!\n",i);
			return(n);
		}
		if(G0[i]->willSurvive==1) n++;
	}
	return(n);
}

int howmany1(){
	int n,i;
	
	n=0;
	for(i=0;i<maxN1;i++){
		if(G1[i]==NULL){
			printf("\nmemory leak at i=%i!\n",i);
			return(n);
		}
		if(G1[i]->willSurvive==1) n++;
	}
	return(n);
}

int howmanyadults(){
	int n,i;
	
	n=0;
	for(i=0;i<maxN;i++){
		if(G0[i]->willSurvive==1 && G0[i]->age>0) n++;
	}
	return(n);
}

int findWhere(int n){
	int res;
	int i;
	
	res = 0;
	i=0;
	while(G0[i]->willSurvive>0){
		i++;
		if(i==(capacity[n]-1)) break;
	}
	if(i<capacity[n]){ res=i;}
	return(res);
}

int findWhere1(int n){
	int res;
	int i;
	
	res = 0;
	i=0;
	while(G1[i]->willSurvive>0){
		i++;
		if(i==(capacity1[n]-1)) break;
	}
	if(i<capacity1[n]){ res=i;}
	return(res);
}

void swinger(float f12, float f21, int count){
  int i,j,nm,nm1,mx,pos;
  founder *tmp;
  
  nm=howmany();
  nm1=howmany1();
  if(nm>nm1) mx=nm;
  else mx=nm1;
  
  tmp=malloc(mx*sizeof(founder));
  for(i=0;i<mx;i++){
    tmp[i]=malloc(sizeof(gad));
    tmp[i]->aa1=malloc(param.aaLength*sizeof(int));
    tmp[i]->aa2=malloc(param.aaLength*sizeof(int));
    tmp[i]->nuc=malloc(param.nucLength*sizeof(int));
    tmp[i]->willSurvive=0;
  }
  j=0;
  for(i=0;i<nm;i++){
    if((gsl_rng_uniform(r)<f12) || (G0[i]->willSurvive==1)){
      copygad(G0[i],tmp[j]);
      tmp[j]->willSurvive=1;
      G0[i]->willSurvive=0;
      j++;
    }
  }
  for(i=0;i<nm1;i++){
    if((gsl_rng_uniform(r)<f21) || (G1[i]->willSurvive==1)){
      pos=findWhere(0);
      copygad(G1[i],G0[pos]);
      G1[i]->willSurvive=0;
    }
  }
  for(i=0;i<j;i++){
      pos=findWhere1(0);
      copygad(tmp[i],G1[pos]);
      G1[pos]->willSurvive=1;
  }
  for(i=0;i<mx;i++){
    free(tmp[i]->nuc);
    free(tmp[i]->aa1);
    free(tmp[i]->aa2);
  }
  free(tmp);
  return;
}

void sampleNuc(int n, int m){
	FILE *ff;
	int i,j,k;
	int *sample;
	char ch[10];
	
	sample=malloc(n*sizeof(int));
	sample[0]=gsl_rng_uniform_int(r,m);
	for(i=1;i<n;){
		sample[i]=gsl_rng_uniform_int(r,m);
		k=0;
		for(j=0;j<i;j++){
			if(sample[i]==sample[j]) k=1;
		}
		if(!k) i++;
	}
	ff=fopen("sample.phy","w");
	fprintf(ff,"%i  %i\n",n*2+1,param.nucLength);
	fprintf(ff,"OUTGROUP  ");
	for(j=0;j<param.nucLength;j++){
		k=(int)fd->nuc[j];
		fprintf(ff,"%c",nucleotides[k]);
	}
	fprintf(ff,"\n");
	for(i=0;i<n;i++){
		sprintf(ch,"Spec%i",sample[i]);
		fprintf(ff,"%s",ch);
		k=10-strlen(ch);
		for(j=0;j<k;j++) fprintf(ff," ");
		for(j=0;j<param.nucLength;j++){
			k=(int)G0[i]->nuc[j];
			fprintf(ff,"%c",nucleotides[k]);
		}
		fprintf(ff,"\n");
	}
	fclose(ff);
	free(sample);
	return;
}

void sampleNuc1(int n, int m){
	FILE *ff;
	int i,j,k;
	int *sample;
	char ch[10];
	
	sample=malloc(n*sizeof(int));
	sample[0]=gsl_rng_uniform_int(r,m);
	for(i=1;i<n;){
		sample[i]=gsl_rng_uniform_int(r,m);
		k=0;
		for(j=0;j<i;j++){
			if(sample[i]==sample[j]) k=1;
		}
		if(!k) i++;
	}
	ff=fopen("sample.phy","a");
	//fprintf(ff,"%i  %i\n",n,param.nucLength);
	for(i=0;i<n;i++){
		sprintf(ch,"Sp_2%i",sample[i]);
		fprintf(ff,"%s",ch);
		k=10-strlen(ch);
		for(j=0;j<k;j++) fprintf(ff," ");
		for(j=0;j<param.nucLength;j++){
			k=(int)G1[i]->nuc[j];
			fprintf(ff,"%c",nucleotides[k]);
		}
		fprintf(ff,"\n");
	}
	fclose(ff);
	free(sample);
	return;
}

void sampleAA(int n, int m){
  FILE *ff;
  int i,j,k;
  char ch[10];
  int *sample;
  
  sample = malloc(n*sizeof(int));
  sample[0]=gsl_rng_uniform_int(r,m);
  for(i=1;i<n;){
    sample[i]=gsl_rng_uniform_int(r,m);
    k=0;
    for(j=0;j<i;j++){
      if(sample[i]==sample[j]) k=1;
    }
    if(!k) i++;
  }
  ff=fopen("samplAA.phy","w");
  fprintf(ff,"%i %i\n",2*n+1,param.aaLength);
  fprintf(ff,"OUTGROUP  ");
	for(j=0;j<param.aaLength;j++){
		k=(int)fd->aa1[j];
		fprintf(ff,"%c",aacids[k]);
	}
  fprintf(ff,"\n");
  for(i=0;i<n;i++){
		sprintf(ch,"Spec1%i",sample[i]);
		fprintf(ff,"%s",ch);
		k=10-strlen(ch);
		for(j=0;j<k;j++) fprintf(ff," ");
		if(gsl_rng_uniform(r)>.5){
			for(j=0;j<param.aaLength;j++){
				k=(int)G0[i]->aa1[j];
				fprintf(ff,"%c",aacids[k]);
			}
			fprintf(ff,"\n");
		} else {
		for(j=0;j<param.aaLength;j++){
				k=(int)G0[i]->aa2[j];
				fprintf(ff,"%c",aacids[k]);
			}
			fprintf(ff,"\n");
		}
	}
  free(sample);
  fclose(ff);
  return;
}

void sampleAa1(int n, int m){
  FILE *ff;
  int i,j,k;
  char ch[10];
  int *sample;
  
  sample = malloc(n*sizeof(int));
  sample[0]=gsl_rng_uniform_int(r,m);
  for(i=1;i<n;){
    sample[i]=gsl_rng_uniform_int(r,m);
    k=0;
    for(j=0;j<i;j++){
      if(sample[i]==sample[j]) k=1;
    }
    if(!k) i++;
  }
  ff=fopen("samplAA.phy","a");
  fprintf(ff,"\n");
  for(i=0;i<n;i++){
		sprintf(ch,"Sp_2%i",sample[i]);
		fprintf(ff,"%s",ch);
		k=10-strlen(ch);
		for(j=0;j<k;j++) fprintf(ff," ");
		if(gsl_rng_uniform(r)>.5){
			for(j=0;j<param.aaLength;j++){
				k=(int)G1[i]->aa1[j];
				fprintf(ff,"%c",aacids[k]);
			}
			fprintf(ff,"\n");
		} else {
		for(j=0;j<param.aaLength;j++){
				k=(int)G1[i]->aa2[j];
				fprintf(ff,"%c",aacids[k]);
			}
			fprintf(ff,"\n");
		}
	}
  free(sample);
  fclose(ff);
  return;
}
int mate(int n){
	int i,j,k,jf,jm,len,sum,crit,l,q;
	int *par,*f,*m;
	family *fam;
	double v;
	pnums rn;
	
	par = malloc(capacity[n]*sizeof(int));
	f = malloc(capacity[n]*sizeof(int));
	m = malloc(capacity[n]*sizeof(int)); 
	j=0;
	jf=0;
	jm=0;
	
	for(i=0;i<capacity[n];i++){
		if(G0[i]->willSurvive){
			par[j]=i;
			if(oneoftwo()){
				f[jf]=i;
				jf++;
			} else {
				m[jm]=i;
				jm++;
			}
			j++;
		}
	}
	if(jm>jf){
		fam = malloc(jf*sizeof(family));
		len=jf;
	} else {
		fam = malloc(jm*sizeof(family));
		len = jm;
	}
	rn = newPoissonSet(len);
	fillPoissonSet(rn,param.kids);
	/**************************************
	 *	
	 *	HERE WE NUST TAKE INTO ACCOUNT THAT THE
	 *	NUMBER OF PROGENY MAY BE MUCH MORE, THEN 
	 *	MAX NUMBER OF INDIVIDUALS. THERE ARE 2
	 *	APPROACHES TO THAT:
	 *	1) DECREASE EVERYBODY'S VIABILITY BY A COEFFICIENT and let the fitness play later
	 *	2) mix the 2 factors together and let them play here 
	 *	
	 ***************************************/
	sum=0;
	for(i=0;i<len;i++) sum +=rn->val[i];
	//printf("sum=%i capacity=%i there are %i\n",sum,capacity[n],howmany());
	if(sum>capacity[n]) v=(double)capacity[n]/(double)sum;
	else {v=1.0;}
	for(i=0;i<len;i++){
		k=gsl_rng_uniform_int(r,jm);
		fam[i].dad =m[k];
		for(j=k;j<jm-1;j++){
			m[j]=m[j+1];
		}
		jm--;
		k=gsl_rng_uniform_int(r,jf);
		fam[i].mom =f[k];
		for(j=k;j<jf-1;j++){
			f[j]=f[j+1];
		}
		jf--;
	}
	for(i=0;i<len;i++){
		k=rn->val[i];
		for(j=0;j<k;j++){
			if(gsl_rng_uniform(r)<v){
				crit=findWhere(n);
				G0[crit]->age=0;
				G0[crit]->willSurvive=1;
				G0[crit]->fitness=1.0*v;
				q=fam[i].mom;
				for(l=0;l<param.nucLength;l++) G0[crit]->nuc[l]=G0[q]->nuc[l];
				if(oneoftwo()){
					for(l=0;l<param.aaLength;l++) G0[crit]->aa1[l]=G0[q]->aa1[l];
				} else {
					for(l=0;l<param.aaLength;l++) G0[crit]->aa1[l]=G0[q]->aa2[l];
				}
				q=fam[i].dad;
				if(oneoftwo()){
					for(l=0;l<param.aaLength;l++) G0[crit]->aa2[l]=G0[q]->aa1[l];
				} else {
					for(l=0;l<param.aaLength;l++) G0[crit]->aa2[l]=G0[q]->aa2[l];
				}
				//G0[crit]->fitness=howFit(G0[crit],pttrn);
			}
		}
	}
	free(rn);
	free(fam);
	free(f);
	free(m);
	free(par);
	return(0);
}

int mate1(int n){
	int i,j,k,jf,jm,len,sum,crit,l,q;
	int *par,*f,*m;
	family *fam;
	double v;
	pnums rn;
	
	par = malloc(capacity1[n]*sizeof(int));
	f = malloc(capacity1[n]*sizeof(int));
	m = malloc(capacity1[n]*sizeof(int)); 
	j=0;
	jf=0;
	jm=0;
	
	for(i=0;i<capacity1[n];i++){
		if(G1[i]->willSurvive){
			par[j]=i;
			if(oneoftwo()){
				f[jf]=i;
				jf++;
			} else {
				m[jm]=i;
				jm++;
			}
			j++;
		}
	}
	if(jm>jf){
		fam = malloc(jf*sizeof(family));
		len=jf;
	} else {
		fam = malloc(jm*sizeof(family));
		len = jm;
	}
	rn = newPoissonSet(len);
	fillPoissonSet(rn,param.kids);
	/**************************************
	 *	
	 *	HERE WE NUST TAKE INTO ACCOUNT THAT THE
	 *	NUMBER OF PROGENY MAY BE MUCH MORE, THEN 
	 *	MAX NUMBER OF INDIVIDUALS. THERE ARE 2
	 *	APPROACHES TO THAT:
	 *	1) DECREASE EVERYBODY'S VIABILITY BY A COEFFICIENT and let the fitness play later
	 *	2) mix the 2 factors together and let them play here 
	 *	
	 ***************************************/
	sum=0;
	for(i=0;i<len;i++) sum +=rn->val[i];
//printf("sum=%i capacity=%i there are %i\n",sum,capacity1[n],howmany1());
	if(sum>capacity1[n]) v=(double)capacity1[n]/(double)sum;
	else {v=1.0;}
	for(i=0;i<len;i++){
		k=gsl_rng_uniform_int(r,jm);
		fam[i].dad =m[k];
		for(j=k;j<jm-1;j++){
			m[j]=m[j+1];
		}
		jm--;
		k=gsl_rng_uniform_int(r,jf);
		fam[i].mom =f[k];
		for(j=k;j<jf-1;j++){
			f[j]=f[j+1];
		}
		jf--;
	}
	for(i=0;i<len;i++){
		k=rn->val[i];
		for(j=0;j<k;j++){
			if(gsl_rng_uniform(r)<v){
				crit=findWhere1(n);
				G1[crit]->age=0;
				G1[crit]->willSurvive=1;
				G1[crit]->fitness=1.0*v;
				q=fam[i].mom;
				for(l=0;l<param.nucLength;l++) G1[crit]->nuc[l]=G1[q]->nuc[l];
				if(oneoftwo()){
					for(l=0;l<param.aaLength;l++) G1[crit]->aa1[l]=G1[q]->aa1[l];
				} else {
					for(l=0;l<param.aaLength;l++) G1[crit]->aa1[l]=G1[q]->aa2[l];
				}
				q=fam[i].dad;
				if(oneoftwo()){
					for(l=0;l<param.aaLength;l++) G1[crit]->aa2[l]=G1[q]->aa1[l];
				} else {
					for(l=0;l<param.aaLength;l++) G1[crit]->aa2[l]=G1[q]->aa2[l];
				}
				//G0[crit]->fitness=howFit(G0[crit],pttrn);
			}
		}
	}
	free(rn);
	free(fam);
	free(f);
	free(m);
	free(par);
	return(0);
}

void survive(int n){
	int i,ct,count,k;
	double surv;

	//ct = howmanyadults();
	ct=howmany();
	//surv=1.0-pow(((double)ct/(double)capacity[n]),2.0);
	surv=1.7-((double)ct/(double)capacity[n]);
	count=0;
	k=0;
	for(i=0;i<ct;){
		if(G0[count]->willSurvive){
			G0[count]->fitness *= surv;
			growUp(G0[count]);
			if(gsl_rng_uniform(r)>G0[count]->fitness) G0[count]->willSurvive=0;
			i += 1;
		} else {
			k += 1;
		}
		count++;
	}
	return; 
}

void survive1(int n){
	int i,ct,count,k;
	double surv;

	//ct = howmanyadults();
	ct=howmany1();
	//surv=1.0-pow(((double)ct/(double)capacity[n]),2.0);
	surv=1.7-((double)ct/(double)capacity1[n]);
	count=0;
	k=0;
	for(i=0;i<ct;){
		if(G1[count]->willSurvive){
			G1[count]->fitness *= surv;
			growUp(G1[count]);
			if(gsl_rng_uniform(r)>G1[count]->fitness) G1[count]->willSurvive=0;
			i += 1;
		} else {
			k += 1;
		}
		count++;
	}
	return; 
}

double aver(){
	int i,j,i1,j1,k,n;
	int s1,s2;
	double ratio;
	
	n=howmany();
	i1=0;
	j1=0;
	s2=0;
	s1=0;
	for(i=1;i<n;i++){
		if(G0[i]->willSurvive){
			i1++;
			for(j=0;j<i;j++){
				if(G0[j]->willSurvive){
					j1++;
					s2++;
					for(k=0;k<param.nucLength;k++){
						if(G0[i]->nuc[k]!=G0[j]->nuc[k]) s1++;
					}
				}
			}
		}
	}
	ratio=(double)s1/(double)s2/(double)param.nucLength;		
	return(ratio);
}

double dst(int m, int n){
  int i,c1,c2;
  double rr;

  c1=0;
  c2=0;
  for(i=0;i<param.nucLength;i++){
    if(G0[m]->nuc[i]==G0[n]->nuc[i]) c1++;
    else c2++;
    rr=(double)c2/(double)(c1+c2);        /* WATCH OUT HERE!!!!*/
    rr=-log(1-4.0*rr/3.0);
  }
  return(rr);
}

divers dist(int m, int n){
  int i,c1,c2;
  divers rr;

  c1=0;
  c2=0;
  for(i=0;i<param.nucLength;i++){
    if(G0[m]->nuc[i]==G0[n]->nuc[i]) c1++;
    else c2++;
    rr.nuc0=(double)c2/(double)(c1+c2);        /* WATCH OUT HERE!!!!*/
    rr.nuc0=-log(1-4.0*rr.nuc0/3.0);
  }
  c1=0;
  c2=0;
  for(i=0;i<param.nucLength;i++){
    if(G1[m]->nuc[i]==G1[n]->nuc[i]) c1++;
    else c2++;
    rr.nuc1=(double)c2/(double)(c1+c2);        
    rr.nuc1=-log(1-4.0*rr.nuc1/3.0);
  }
  c1=0;
  c2=0;
  for(i=0;i<param.aaLength;i++){
    if(G0[m]->aa1[i]==G0[n]->aa1[i]) c1++;
    else c2++;
    if(G0[m]->aa2[i]==G0[n]->aa2[i]) c1++;
    else c2++;
    rr.aa0=(double)c2/(double)(c1+c2);        
    rr.aa0=-log(1-4.0*rr.aa0/3.0);
  }
  c1=0;
  c2=0;
  for(i=0;i<param.aaLength;i++){
    if(G1[m]->aa1[i]==G1[n]->aa1[i]) c1++;
    else c2++;
    if(G1[m]->aa2[i]==G1[n]->aa2[i]) c1++;
    else c2++;
    rr.aa1=(double)c2/(double)(c1+c2);        
    rr.aa1=-log(1-4.0*rr.aa1/3.0);
  }
  return(rr);
}