#include "parameters.h"

void readparams(){
    FILE *f;
    char *tmp;
    char *q;
    
    tmp=malloc(264*sizeof(char));
    f=fopen("params.ctl","r");
    q=fgets(tmp,255,f);
    param.nucLength = atoi(tmp);
    q=fgets(tmp,255,f);
    param.aaLength = atoi(tmp);
    q=fgets(tmp,255,f);
    param.kids = atoi(tmp);
    q=fgets(tmp,255,f);
    param.maxLife = atoi(tmp);
    q=fgets(tmp,255,f);
    param.mutprob1 = atof(tmp);
    q=fgets(tmp,255,f);
    param.mutprob2 = atof(tmp);
    q=fgets(tmp, 255, f);
	param.numRep=atoi(tmp);
    q=fgets(tmp, 255, f);
	param.epyN=atoi(tmp);
	q=fgets(tmp, 255, f);
	param.Dw=atof(tmp);
    fclose(f);
    free(tmp);
    return;
}
