#include "lib/includes.h"

#define TRIALS 100
#define MAX 1e4
#define N (TRIALS*MAX)

#define MEAN 2
#define VARI 1
#define X_MIN (int)( MEAN - 3*sqrt(VARI) )
#define X_MAX (int)( MEAN + 3*sqrt(VARI) )

void block_average(char* raw_file, char* out_file, int n, int max);
void plot(char** file_names, int n);

int main(void){
	char* raw_data = "out/toi6_raw_data.csv";

    // printf("prepare raw data \n");
    FILE* fp;
	fp = fopen(raw_data, "w");
	for(int i=0; i<N/2; i++){
		double* temp = box_muller_gaussian(MEAN, VARI);
		fprintf(fp, "%lf\n%lf\n", temp[0], temp[1]);
	}
	fclose(fp);

	char* file_names_block_ave[TRIALS];
	for(int i=0; i<TRIALS; i++){
		file_names_block_ave[i] = (char*)malloc(256 * sizeof(char));
		sprintf(file_names_block_ave[i], "out/toi6_%dblock_ave_data.csv", i+1);
	}
	
	for(int i=0; i<TRIALS; i++){
		block_average(raw_data, file_names_block_ave[i], (i+1), MAX);
	}

    fp = fopen("out/toi6_std_dev.csv", "w");
    for(int i=0; i<TRIALS; i++){
		double std_dev = calc_std_dev(file_names_block_ave[i], MAX);
		fprintf(fp, "%d,%lf\n", i+1, std_dev);
	}
	fclose(fp);

	FILE* gid = NULL;
	gid = popen("gnuplot", "w");
	fprintf(gid," set datafile separator ','\n");
	fprintf(gid," set xrange [1:%d]\n", TRIALS);
	fprintf(gid, " set yrange [0:1.2]\n");
	fprintf(gid, "set xlabel 'Number of Samples per Mean'\n");
	fprintf(gid, "set ylabel 'standard deviance'\n");
	fprintf(gid," plot 'out/toi6_std_dev.csv' with line title 'standard devience'\n");
	fprintf(gid," pause 30\n");
	pclose(gid);

	return 0;
}

void block_average(char* raw_file, char *out_file, int n, int max){
	FILE* fp_raw; FILE* fp_out;
	fp_raw = fopen(raw_file, "r");
	fp_out = fopen(out_file, "w");

    double temp;
    for(int i=0; i<max; i++){
    	double sum = 0;
		for(int j=0; j<n; j++){
			fscanf(fp_raw, "%lf\n", &temp);
			sum += temp;
		}
		fprintf(fp_out, "%lf\n", sum / (double)n);
	}

	fclose(fp_raw);
	fclose(fp_out);
}
