#include "fourier_trans.h"

// return the complex which has maximam absolute value
comp max_abs(int size, comp** vec){
	comp max = vec[0][0];
	for(int i=0; i<size; i++){
		if(cabs(max) < cabs(vec[i][0]) ){
			max = vec[i][0];
		}
	}
	return max;
}

int max_point(int size, comp** vec){
    int min;
	if(size%2 == 0){ min = -1 * size / 2;
	}else{ min = -1 * (size-1) / 2; }

	comp max = vec[0][0];
	int max_id = min;
	int count = min;
	for(int i=0; i<size; i++){
		if(cabs(max) < cabs(vec[i][0]) ){
			max = vec[i][0];
			max_id = count;
		}
		count++;
	}
	
	return max_id;
}

double calc_distance(comp** y_vector_s1, comp** coef_mat_s1, comp** y_vector_s2, comp** coef_mat_s2){
	// apply fourier transformation
	comp** coef_vec_s1 = fourier_transform(y_vector_s1, coef_mat_s1, SIZE_POINT);
	comp** coef_vec_s2 = fourier_transform(y_vector_s2, coef_mat_s2, SIZE_POINT);

    // search the beggest coefficient and convert it to phase angle
    comp coef_main_s1 = max_abs(SIZE_POINT, coef_vec_s1);
	double theta_s1 = carg(coef_main_s1);
	comp coef_main_s2 = max_abs(SIZE_POINT, coef_vec_s2);
	double theta_s2 = carg(coef_main_s2);

	// theta_s1 - theta_s2 = 4PI/LIGHT_SPEED * (-F1 + F2) * R
	double k = 4*PI/LIGHT_SPEED * (-F1+F2);

	// format theta value
	double delta = theta_s1 - theta_s2;
	if (delta < 0){ delta += 2*PI; }

	double dist = delta / k;
	return dist;
}

double calc_vel(comp** y_vector_s1, comp** coef_mat_s1, comp** y_vector_s2, comp** coef_mat_s2){
	// apply fourier transformation
	comp** coef_vec_s1 = fourier_transform(y_vector_s1, coef_mat_s1, SIZE_POINT);
	comp** coef_vec_s2 = fourier_transform(y_vector_s2, coef_mat_s2, SIZE_POINT);

	// search max point
	int max_component_s1 = max_point(SIZE_POINT, coef_vec_s1);
	int max_component_s2 = max_point(SIZE_POINT, coef_vec_s2);

	double freq_s1 = (double)max_component_s1 / SIZE_POINT * SAMPLE_FREQ;
	double freq_s2 = (double)max_component_s2 / SIZE_POINT * SAMPLE_FREQ;

	double lambda_s1 = (double)LIGHT_SPEED / F1;
	double lambda_s2 = (double)LIGHT_SPEED / F2;

	double vel_s1 = lambda_s1 * freq_s1 / 2;
	double vel_s2 = lambda_s2 * freq_s2 / 2;
	
	return (vel_s1 + vel_s2) / 2;
}

comp** fourier_transform(comp** y_vector, comp** coef_mat, int size_point){
    // calculate ans_vector = (X^t X)^{-1} X^t y
    // matA = X^t X, matB = (X^t X)^{-1} X^t
    comp** t_coef_mat = calc_transp_mat(size_point, size_point, coef_mat);
    comp** matA = calc_multipl_mat(size_point, size_point, size_point, t_coef_mat, coef_mat);
    comp** inv_matA = calc_inverse_mat(size_point, matA);
    comp** matB = calc_multipl_mat(size_point, size_point, size_point, inv_matA, t_coef_mat);
    comp** ans_vector = calc_multipl_mat(size_point, size_point, 1, matB, y_vector);

    return ans_vector;
}

comp** fourier_series_expansion(comp** y_vector, comp** coef_mat, int size_point, int size_degree){
    // calculate ans_vector = (X^t X)^{-1} X^t y
    // matA = X^t X, matB = (X^t X)^{-1} X^t
    comp** t_coef_mat = calc_transp_mat(size_point, size_degree, coef_mat);
    comp** matA = calc_multipl_mat(size_degree, size_point, size_degree, t_coef_mat, coef_mat);
	comp** inv_matA = calc_inverse_mat(size_degree, matA);
	comp** matB = calc_multipl_mat(size_degree, size_degree, size_point, inv_matA, t_coef_mat);
	comp** ans_vector = calc_multipl_mat(size_degree, size_point, 1, matB, y_vector);

    return ans_vector;
}

void show_func(double** coef_vec, int size_degree){
    printf("%d degree fitted function : ", size_degree);
    printf("y = ");
    for(int i=0; i<size_degree+1; i++){
        // decrealar "+"
        if (coef_vec[size_degree - i][0] >= 0.0 && i!=0){printf("+");}
        printf("%f", coef_vec[size_degree - i][0]);
        switch(size_degree - i){
            case 0:
                printf("\n");
                break;
            case 1:
                printf(" x ");
                break;
            default:
                printf(" x^%d ", size_degree - i);
                break;
        }
    }
	printf("\n");
}

double** multi_fitting(double** y_vector, double** coef_mat, int size_point, int size_degree){
    // calculate ans_vector = (X^t X)^{-1} X^t y
    // matA = X^t X, matB = (X^t X)^{-1} X^t
    double** t_coef_mat = double_calc_transp_mat(size_point, size_degree+1, coef_mat);
    double** matA = double_calc_multipl_mat(size_degree+1, size_point, size_degree+1, t_coef_mat, coef_mat);
    double** inv_matA = double_calc_inverse_mat(size_degree+1, matA);
    double** matB = double_calc_multipl_mat(size_degree+1, size_degree+1, size_point, inv_matA, t_coef_mat);
    double** ans_vector = double_calc_multipl_mat(size_degree+1, size_point, 1, matB, y_vector);

    show_func(ans_vector, size_degree);

    return ans_vector;
}