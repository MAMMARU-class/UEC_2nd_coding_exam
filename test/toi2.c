#include "lib/includes.h"
#define N 3

int main(void){
	comp** mat_a = get_matrix("data/toi2_mat_a.csv", N, N);
	comp** inv_a = calc_inverse_mat(N, mat_a);

	printf("inverted matrix : \n");
	show_matrix(N, N, inv_a);
}