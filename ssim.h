#ifndef __SSIM_H
#define __SSIM_H

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_histogram.h>
#include "utils.h"
#include "fate.h"
#include "parameters.h"
#include "gad.h"

#define VERSION "0.3.0"
#define MUTSTEPS 30
#define AMUTSTEPS 10

int i,j,count,bot,x,y,z;
int num,num1;
double **growthCurves;
double *distribND;
double Nmax, Nmin,delta,norm,dmax,dts;
gsl_histogram *h,*g;

char buf1[50];
gad *fder, *fder1;
FILE *ffile,*f1,*f2,*f3;
#endif
