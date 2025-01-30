#include "lib/includes.h"

#define N 100
#define K 30

int main(void){
    // template
	comp** y_vec = (comp**)malloc(N * sizeof(comp*));
	for(int i=0; i<N; i++){
		y_vec[i] = malloc(1 * sizeof(comp));
	}
	comp** coef_mat = (comp**)malloc(N * sizeof(comp*));
	for(int i=0; i<N; i++){
		coef_mat[i] = malloc(K * sizeof(comp));
	}

	fourier_format_pointsfile("data/toi3_data.csv", N, K, y_vec, coef_mat);
	comp** ans_coef_mat = fourier_series_expansion(y_vec, coef_mat, N, K);
	comp** ans_points = calc_multipl_mat(N, K, 1, coef_mat, ans_coef_mat);
	
    // write points data to csv
    FILE* fp;
	fp = fopen("out/toi3_ans.csv", "w");
	for(int i=0; i<N; i++){
		fprintf(fp, "%d,%lf\n", i, creal(ans_points[i][0]));
	}
	fclose(fp);

    // plot
	FILE* gid = NULL;
	gid = popen("gnuplot","w");
	fprintf(gid, "set datafile separator ','\n");
	fprintf(gid, "set xrange [0:100]\n");
	fprintf(gid, "set yrange [-0.5:1.5]\n");
	fprintf(gid, "set xlabel 'time'\n");
	fprintf(gid, "set ylabel 'value'\n");
	fprintf(gid," plot 'data/toi3_data.csv' pt 1 title 'original points'\n");
	fprintf(gid," replot 'out/toi3_ans.csv' with line title '%d degree transformed function'\n", K);
	fprintf(gid," pause 30\n");
	pclose(gid);

	return 0;
}
