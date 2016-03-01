#ifndef __FATE_H
#define __FATE_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int steps;    //number of generations
int maxN,maxN1;	  // max number of organisms
int *capacity,*capacity1; //capacity of environment and swinging schedule
float *swing12, *swing21;
void line(int length, char* fn, int startNum, int endNum);
void line1(int length, char* fn, int startNum, int endNum);
int readfate(char *fn);
void readM();
#endif
