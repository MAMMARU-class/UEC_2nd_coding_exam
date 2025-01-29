#include "comp_calc.h"

// calculation functions
comp** calc_multipl_mat(int ans_col_size, int middle_size, int ans_row_size, comp** multcand, comp** multpler){
    comp** ans_mat = (comp**)malloc(ans_col_size * sizeof(comp*));
    for(int i=0; i<ans_col_size; i++){
        ans_mat[i] = (comp*)malloc(ans_row_size * sizeof(comp));
    }
    // initialize 0 and set multiple ans
    for(int i=0; i<ans_col_size; i++){
        for(int j=0; j<ans_row_size; j++){
            ans_mat[i][j] = 0;
            for(int k=0; k<middle_size; k++){
                ans_mat[i][j] += multcand[i][k] * multpler[k][j];
            }
        }
    }

    return ans_mat;
}

comp** calc_transp_mat(int col_size, int row_size, comp** mat){
    comp** transp_mat = (comp**)malloc(row_size * sizeof(comp*));
    for(int i=0; i<row_size; i++){
        transp_mat[i] = (comp*)malloc(col_size * sizeof(comp));
    }

    for(int i=0; i<col_size; i++){
        for(int j=0; j<row_size; j++){
            transp_mat[j][i] = conj(mat[i][j]);
        }
    }

    return transp_mat;
}

comp** calc_inverse_mat(int size, comp** mat)
{
    // create matrix template
    comp** inverse = (comp**)malloc(size * sizeof(comp*));
    for(int i=0; i<size; i++){
        inverse[i] = (comp*)malloc(size * sizeof(comp));
    }
    // init inverse matrix with identity matrix
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(i==j){inverse[i][j] = 1;
            }else{inverse[i][j] = 0;}
        }
    }

    // delete
	comp c;
    for(int k=0; k<size-1; k++){ // from first row to 1 before the last row
		for(int i=k+1; i<size; i++){ // from one after the youngest colnum which left its k row (which is k colnum)
			c=(mat[i][k]/mat[k][k]); // delete k row using k colnum
			for(int j=0; j<size ;j++){ // for every rows
				mat[i][j] = mat[i][j]-mat[k][j]*c;
                inverse[i][j] = inverse[i][j]-inverse[k][j]*c;
			}
		}
	}
    
    // substitution
	for(int k=size-1; k>0; k--){ // frm last row to 1 before the first row
		for(int i=k-1; i>=0; i--){
			c=(mat[i][k]/mat[k][k]); // delete k row using k colnum
			for(int j=size-1; j>=0; j--){
				mat[i][j] = mat[i][j]-mat[k][j]*c;
                inverse[i][j] = inverse[i][j]-inverse[k][j]*c;
			}
		}
	}

    // change diagonals to 1
	for(int i=0; i<size; i++){
		c=1/mat[i][i];
        for(int j=0; j<size; j++){
            inverse[i][j] *= c;
        }
	}

    return inverse;
}
