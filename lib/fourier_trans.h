/*
フーリエ変換、および距離の算出プログラム
*/

#ifndef calc_dist
#define calc_dist

#include "comp_calc.h"
#include "setting.h"

// CW sensor
#define F1 ( 24.05120 * 1e9 )
#define F2 ( 24.08320 * 1e9 )

#define SIZE_POINT 128
#define SAMPLE_FREQ 1e3

double calc_distance(comp** y_vector_s1, comp** coef_mat_s1, comp** y_vector_s2, comp** coef_mat_s2);
double calc_vel(comp** y_vector_s1, comp** coef_mat_s1, comp** y_vector_s2, comp** coef_mat_s2);
// returns coeficient vector
comp** fourier_transform(comp** y_vector, comp** mat, int size_point);
comp** fourier_series_expansion(comp** y_vector, comp** coef_mat, int size_point, int size_degree);

#endif
