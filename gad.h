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
 ********/

#ifndef __GAD_H
#define __GAD_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_histogram.h>
#include "utils.h"
#include "fate.h"
#include "parameters.h"
#include <string.h>
#define startN 100

typedef struct gad {
	int age;
	int willSurvive;
	double fitness;
	int *aa1;
	int *aa2;
	int *nuc;
} *founder,gad;

typedef struct point {
	int x;
	int y;
	int z;
} point;

typedef struct family {
	int dad;
	int mom;
} family;

/*pairwise distances for the 2 species*/
typedef struct divers{
    double nuc0;
    double nuc1;
    double aa0;
    double aa1;
} divers;

point pt;
founder *G0, *G1;
gad *fd;
/*         TEMPLATES          */
void initgad(founder fd, int l1);
void cloneFndr(founder fndr,founder tmp);
void growUp(founder g);
void aaMut(founder g);
void aaMut2(founder g);
void nucMut(founder g);
void killTvar(founder tv);
void copygad(founder src, founder target);
void start(founder f);
void start1(founder f);
int howmany();
int howmany1();
int howmanyadults();
void swinger(float f12, float f21, int count);
void sampleNuc(int n, int m);
void sampleNuc1(int n, int m);
void sampleAA(int n, int m);
void sampleAa1(int n, int m);
int mate(int n);
int mate1(int n);
void survive(int n);
void survive1(int n);
double aver();
double dst(int m, int n);
divers dist(int m, int n);
#endif
