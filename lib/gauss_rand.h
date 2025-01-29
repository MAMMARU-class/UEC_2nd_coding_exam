#ifndef gauss_rand
#define gauss_rand

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "setting.h"

#define GAUSS_ACCUR 1000

double clt_gaussian(int mean, int variance);
// return 2 gaussian numbers
double* box_muller_gaussian(int mean, int variance);

double calc_std_dev(char* file_name, int size);

#endif
