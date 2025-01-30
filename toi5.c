#include "lib/includes.h"

int main(void){
	// create template
    comp** y_vector_s1 = (comp**)malloc(SIZE_POINT * sizeof(comp*));
    for(int i=0; i<SIZE_POINT; i++){
        y_vector_s1[i] = (comp*)malloc(1 * sizeof(comp));
    }
    comp** coef_mat_s1 = (comp**)malloc(SIZE_POINT * sizeof(comp*));
    for(int i=0; i<SIZE_POINT; i++){
        coef_mat_s1[i] = (comp*)malloc( (SIZE_POINT) * sizeof(comp));
    }

    comp** y_vector_s2 = (comp**)malloc(SIZE_POINT * sizeof(comp*));
    for(int i=0; i<SIZE_POINT; i++){
        y_vector_s2[i] = (comp*)malloc(1 * sizeof(comp));
    }
    comp** coef_mat_s2 = (comp**)malloc(SIZE_POINT * sizeof(comp*));
    for(int i=0; i<SIZE_POINT; i++){
        coef_mat_s2[i] = (comp*)malloc( (SIZE_POINT) * sizeof(comp));
    }

    // format
    fourier_format_pointsfile("data/f1.csv", SIZE_POINT, SIZE_POINT, y_vector_s1, coef_mat_s1);
	fourier_format_pointsfile("data/f2.csv", SIZE_POINT, SIZE_POINT, y_vector_s2, coef_mat_s2);

    double vel = calc_vel(y_vector_s1, coef_mat_s1, y_vector_s2, coef_mat_s2);
    double dist = calc_distance(y_vector_s1, coef_mat_s1, y_vector_s2, coef_mat_s2);

	printf("vel = %lf m/s\n", vel);
	printf("dist = %lf m\n", dist);

	return 0;
}
