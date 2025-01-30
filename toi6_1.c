#include "lib/includes.h"

#define TRIALS 20

#define MEAN 4
#define VARI 1

int main(void){
	FILE* fp = fopen("out/toi6_1_data.csv", "w");
	for(int i=0; i<TRIALS; i++){
		double* temp = box_muller_gaussian(MEAN, VARI);
		fprintf(fp, "%d,%lf\n", i+1, temp[0]);
	}
	fclose(fp);

	FILE* gid = NULL;
	gid = popen("gnuplot", "w");
	fprintf(gid," set datafile separator ','\n");
	fprintf(gid," set xrange [%d:%d]\n", 1, TRIALS+1);
	fprintf(gid, " set yrange [%d:%d]\n", MEAN-4, MEAN+4);
	fprintf(gid, "set xlabel 'Number of Samples'\n");
	fprintf(gid, "set ylabel 'value'\n");
	fprintf(gid," plot 'out/toi6_1_data.csv' pt 1 title 'gaussian random values'\n");
	fprintf(gid," pause 30\n");
	pclose(gid);

	return 0;
}
