#include "fate.h"

void line(int length, char* fn, int startNum, int endNum){
	int dY,i,dYY;
	FILE *out;
	
    dY=(int)((float)(endNum-startNum)/(float)length);
    out=fopen(fn,"a");
    for(i=0;i<length;i++){
	dYY=startNum+i*dY;
        fprintf(out,"%i\n",dYY);
		if(dYY>maxN) maxN=dYY;
    }
    fclose(out);
	steps += length;

    return;
}

void line1(int length, char* fn, int startNum, int endNum){
	int dY,i,dYY;
	FILE *out;
	dY=(int)((float)(endNum-startNum)/(float)length);
	out=fopen(fn,"a");
    for(i=0;i<length;i++){
		dYY=startNum+i*dY;
        fprintf(out,"%i\n",dYY);
		if(dYY>maxN1) maxN1=dYY;
    }
    fclose(out);
	steps += length;

    return;
}

int readfate(char *fn){
	static int i,l,stretch,stv,endv,q;
	char *lin,*c;
	char typ;
	FILE *fout, *fin, *fin1;
	
	lin=malloc(50*sizeof(char));
	fin=fopen("envi.ctl","r");
	fin1=fopen("envi1.ctl","r");
	fout = fopen(fn,"w");
	fclose(fout);
	fout = fopen("tmp","w");
	fclose(fout);
	fout = fopen("tmp1","w");
	fclose(fout);
	c=fgets(lin,50,fin);
	l=atoi(lin);

	maxN=0;
	for(i=0;i<l;i++){
		c=fgets(lin,50,fin);
		sscanf(lin,"%c %i %i %i",&typ,&stv,&endv,&stretch);
		printf("\t%i \t%i \t%i\n",stretch,stv,endv);
		if(typ=='l') line(stretch,"tmp",stv,endv);
	}
	
	c=fgets(lin,50,fin1);
	l=atoi(lin);
	printf("\n\n\t\tAssumed scenario for spec.2:\n");
	printf("\tLength\tStart #\t end #\n");
	printf("\t========================\n");

	maxN1=0;
	steps=0;
	for(i=0;i<l;i++){
		c=fgets(lin,50,fin1);
		sscanf(lin,"%c %i %i %i",&typ,&stv,&endv,&stretch);
		printf("\t%i \t%i \t%i\n",stretch,stv,endv);
		if(typ=='l') line1(stretch,"tmp1",stv,endv);
	}
	fclose(fin1);
	fout=fopen(fn,"w");
	fin=fopen("tmp","r");
	fin1=fopen("tmp1","r");
	for(i=0;i<steps;i++){
	  c=fgets(lin,50,fin);
	  sscanf(lin,"%i",&q);
	  fprintf(fout,"%i\t%i\t",i,q);
	  c=fgets(lin,50,fin1);
	  sscanf(lin,"%i",&q);
	  fprintf(fout,"%i\n",q);
	}
	fclose(fout);
	fclose(fin);
	fclose(fin1);
	free(lin);
	return(0);
}

void readM(){
  FILE *fin;
  char *lin,*c;
  int i,st,same,j,j1;
  float f12,f21;
  
  lin=malloc(64*sizeof(char));
  fin=fopen("swing.ctl", "r");
   printf("here1\n");
   if(fin==NULL){
     printf("No file!!!\n");
     return;
   }
  c=fgets(lin,50,fin);
  st=atoi(lin);
  j1=0;
  printf("\n\n\t\tAssumed swinging scenario:\n");
  printf("\tLength\t1->2 \t 2->1#\n");
  printf("\t========================\n");
  for(i=0;i<st;i++){
    if(feof(fin)) break;
    c=fgets(lin,50,fin);
    sscanf(lin,"%i\t%f\t%f",&same,&f12,&f21);
    printf("\t%i\t%4.3f\t%4.3f\n",same,f12,f21);
    for(j=0;j<same;j++){
      swing12[j1]=f12;
      swing21[j1]=f21;
      j1++;
    }
  }
//  free(lin);
  return;
}
	
