
#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <sys/stat.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_histogram.h>
#include <gsl/gsl_histogram2d.h>
#define nucleotides "ACGT"
#define aacids "ACDEFGHIKLMNPQRSTVWY"

/* vars */
time_t tt;
const gsl_rng_type *T;
gsl_rng *r;
struct tm *loctime;
int cc;

typedef struct poisson_set {
	int num;
	int *val;
} *pnums;

/* FUNCTION PROTOTYPES */
void rinit();
int rnucl();
int ramino();
int rpos(int l);
int oneoftwo();
pnums newPoissonSet(int n);
void delPoissonSet(pnums p);
void fillPoissonSet(pnums p, double mu);
#endif
