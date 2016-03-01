#ifndef __PARAM_H
#define __PARAM_H
#include <stdio.h>
#include <stdlib.h>
/*
	read simulation parameters form file
*/
struct {
	int nucLength;
	int aaLength;
	int kids;
	int maxLife;
	double mutprob1;
	double mutprob2;
	int numRep;
	int epyN;		/* Number of "episodes" of equal length to split the history*/
	double Dw;
} param;

void readparams();

#endif

