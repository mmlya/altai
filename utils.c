#include "utils.h"

void rinit(){
	tt=time(0);
	gsl_rng_env_setup();
	T=gsl_rng_default;
	r=gsl_rng_alloc(T);
	gsl_rng_set(r,(long)tt);
	return;
}

int rnucl(){
	return(gsl_rng_uniform_int(r,4));
}

int ramino(){
	return gsl_rng_uniform_int(r,20);
}

int rpos(int l){
	return gsl_rng_uniform_int(r,l);
}

int oneoftwo(){
	if(gsl_rng_uniform(r)<.5) return(0);
	else return(1);
}

pnums newPoissonSet(int n){
	pnums p;
	p = malloc(sizeof(pnums));
	p->val=malloc(n*sizeof(int));
	p->num=n;
	
	return(p);
}

void delPoissonSet(pnums p){
	free(p->val);
	free(p);
}

void fillPoissonSet(pnums p, double mu){
	int i;
	
	for(i=0;i<p->num;i++) p->val[i]=gsl_ran_poisson(r,mu);
	return;
}
