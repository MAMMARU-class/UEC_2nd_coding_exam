#include "lib/includes.h"
#define N 3

int main(void){
	comp** mat = get_matrix("data/toi1_mat.csv", N, N);
	comp** inv = calc_inverse_mat(N, mat);

	printf("inverted matrix : \n");
	show_matrix(N, N, inv);
}
