#include "lib/includes.h"
#define N 3

int main(void){
	comp** mat_a = get_matrix("data/toi2_mat_a.csv", N, N);
	comp** vec_b = get_matrix("data/toi2_vec_b.csv", N, 1);

    // calclation using inverse matrix
	comp** inv_a = calc_inverse_mat(N, mat_a);
	comp** ans = calc_multipl_mat(N, N, 1, inv_a, vec_b);

	printf("answer : \n");
	printf("x = %lf\n", creal(ans[0][0]));
	printf("y = %lf\n", creal(ans[1][0]));
	printf("z = %lf\n", creal(ans[2][0]));
}
