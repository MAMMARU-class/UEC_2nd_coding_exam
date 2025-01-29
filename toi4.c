#include "lib/includes.h"
#define N 4

void plot_func(FILE* gid, double** coef_vec, int size_degree);

int main(void){
	int deg1 = 1; int deg2 = 2;
	double** y_vec = (double**)malloc(N * sizeof(double*));
	for(int i=0; i<N; i++){
		y_vec[i] = (double*)malloc(1 * sizeof(double));
	}
	double** coef_mat_d1 = (double**)malloc(N * sizeof(double*));
	for(int i=0; i<N; i++){
		coef_mat_d1[i] = (double*)malloc(deg1+1 * sizeof(double));
	}
	double** coef_mat_d2 = (double**)malloc(N * sizeof(double*));
	for(int i=0; i<N; i++){
		coef_mat_d2[i] = (double*)malloc(deg2+1 * sizeof(double));
	}

    // format
	fitting_format_pointsfile("data/toi4_data.csv", N, deg1, y_vec, coef_mat_d1);
	fitting_format_pointsfile("data/toi4_data.csv", N, deg2, y_vec, coef_mat_d2);
	
    // 1 and 2 degree fitting
    double** coef_vec_deg1 = multi_fitting(y_vec, coef_mat_d1, N, deg1);
	double** coef_vec_deg2 = multi_fitting(y_vec, coef_mat_d2, N, deg2);

	// plot
	FILE* gid = NULL;
	gid = popen(" gnuplot","w");
	fprintf(gid," set datafile separator ','\n");
	fprintf(gid," set xrange [0:5]\n");
	fprintf(gid, " set yrange [0:20]\n");
	fprintf(gid," plot 'data/toi4_data.csv' pt 1 title 'original points'\n");
	plot_func(gid, coef_vec_deg1, deg1);
	plot_func(gid, coef_vec_deg2, deg2);
	fprintf(gid," pause 30\n");
	pclose(gid);

	return 0;
}

void plot_func(FILE* gid, double** coef_vec, int size_degree)
{
	fprintf(gid, "replot ");
    for(int i=0; i<size_degree+1; i++){
        // decrealar "+"
        if (coef_vec[size_degree - i][0] >= 0.0 && i!=0){fprintf(gid, "+");}
        fprintf(gid, "%f", coef_vec[size_degree - i][0]);
        switch(size_degree - i){
            case 0:
                break;
            default:
                for(int j=0; j<size_degree - i; j++){
                    fprintf(gid, "*x");
                }
                break;
        }
    }
	fprintf(gid, " with line title '%d degree fitting'\n", size_degree);
}