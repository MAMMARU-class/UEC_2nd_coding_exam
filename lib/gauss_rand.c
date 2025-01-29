#include "gauss_rand.h"

double clt_gaussian(int mean, int variance){
	// default mean = 1/2, variance^2 = 1/(12*N)
	double sum = 0;
	for(int i=0; i<GAUSS_ACCUR; i++){
		double temp = rand() / (double)RAND_MAX;
		sum += temp;
	}

    double temp_mean = sum / GAUSS_ACCUR;

    // convert to N(0,1)
	temp_mean = sqrt(12.*GAUSS_ACCUR)*(temp_mean - 0.5);
	// convert to N(mean,variance)
	temp_mean = sqrt(variance)*(temp_mean + mean);

	return temp_mean;
}

double* box_muller_gaussian(int mean, int variance){
	double* temp = (double*)malloc(2 * sizeof(double));
	
	// U(0,1)
	double temp1 = rand() / (double)RAND_MAX;
    // U(0,2*PI)
	double temp2 = ( rand() / (double)RAND_MAX ) * 2*PI;

    // avoid error
    if(temp1 == 0 ){
		temp[0] = mean; temp[1] = mean;
		return temp;
	}
    temp[0] = sqrt(-2. * log(temp1) ) * cos(2.*PI*temp2);
	temp[1] = sqrt(-2. * log(temp1) ) * sin(2.*PI*temp2);
    
	// convert to N(mean,variance)
	for(int i=0; i<2; i++){
		temp[i] = sqrt(variance) * (temp[i] + mean);
	}

	return temp;
}

double calc_std_dev(char* file_name, int size){
	FILE* fp = fopen(file_name, "r");
	double ave;

    double temp;
	double sum=0;
	for(int i=0; i<size; i++){
		fscanf(fp, "%lf\n",  &temp);
		sum += temp;
	}
	ave = sum/(double)size;
	fclose(fp);

	fp = fopen(file_name, "r");
	double a=0;
	for(int i=0; i<size; i++){
		fscanf(fp, "%lf\n",  &temp);
		a += (temp-ave) * (temp-ave);
	}
	fclose(fp);
	
	return sqrt(a/(double)size);
}
