#include "lib/includes.h"
#define N 3

int main(void){
	comp** mat_a = get_matrix("data/toi1_mat_a.csv", N, N);
	comp** vec_b = get_matrix("data/toi1_vec_b.csv", N, 1);

    // calclation using inverse matrix
	// comp** inv_a = calc_inverse_mat(N, mat_a);
	// comp** ans = calc_multipl_mat(N, N, 1, inv_a, vec_b);

    // delete
	comp c;
    for(int k=0; k<N-1; k++){ // from first row to 1 before the last row
		for(int i=k+1; i<N; i++){ // from one after the youngest colnum which left its k row (which is k colnum)
			c=(mat_a[i][k]/mat_a[k][k]); // delete k row using k colnum
			for(int j=0; j<N ;j++){ // for every rows
				mat_a[i][j] = mat_a[i][j]-mat_a[k][j]*c;
			}
			vec_b[i][0] = vec_b[i][0]-vec_b[k][0]*c;
		}
	}
    
    // substitution
	for(int k=N-1; k>0; k--){ // frm last row to 1 before the first row
		for(int i=k-1; i>=0; i--){
			c=(mat_a[i][k]/mat_a[k][k]); // delete k row using k colnum
			for(int j=N-1; j>=0; j--){
				mat_a[i][j] = mat_a[i][j]-mat_a[k][j]*c;
			}
			vec_b[i][0] = vec_b[i][0]-vec_b[k][0]*c;
		}
	}

    // change diagonals to 1
	for(int i=0; i<N; i++){
		c=1/mat_a[i][i];
        vec_b[i][0] *= c;
	}

	printf("answer : \n");
	printf("x = %lf\n", creal(vec_b[0][0]));
	printf("y = %lf\n", creal(vec_b[1][0]));
	printf("z = %lf\n", creal(vec_b[2][0]));
}
