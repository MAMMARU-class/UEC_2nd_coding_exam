#include "file_rw.h"

comp** get_matrix(char* file_name, int size_col, int size_row){
	comp** mat = (comp**)malloc(size_col * sizeof(comp*));
	for(int i=0; i<size_col; i++){
		mat[i] = (comp*)malloc(size_row * sizeof(comp));
	}
	
	FILE* fp;
	fp = fopen(file_name, "r");
	for(int i=0; i<size_col; i++){
		for(int j=0; j<size_row; j++){
			double real, img;
			fscanf(fp, "%lf,%lf,", &real, &img);
			mat[i][j] = real + img * I;
		}
		fscanf(fp, "\n");
	}

	return mat;
}

// show
void show_matrix(int size_col, int size_row, comp** mat){
    for(int col=0; col < size_col; col++){
        for(int row=0; row<size_row; row++){
            printf("%f ", creal(mat[col][row]));
            if(cimag(mat[col][row]) >= 0) printf("+");
            
			printf("%lf i", cimag(mat[col][row]));
            if(row != size_row-1){printf(",  ");}
        }
        printf("\n");
    }
}


void set_base_fourier(double value, int col, comp** coef_mat, int size){
    int min = -(int)size/2;
    for(int i=0; i<size; i++){
        coef_mat[col][i] = cexp(I * 2 * PI * (min + i) * value / size);
    }
}

bool fourier_format_pointsfile(char* file_name, int size, int degree, comp** y_vector, comp** coef_mat){
	FILE *fp;
    fp = fopen(file_name, "r");
    for(int i=0; i<size; i++){
        double x, y_r, y_i;
        fscanf(fp, "%lf,%lf,%lf\n", &x, &y_r, &y_i);
        
		// make coeficient matrix
        y_vector[i][0] = y_r + y_i * I;
        set_base_fourier(x, i, coef_mat, degree);
    }

    fclose(fp);
	return true;
}

void set_base_fitting(double value, int col, comp** coef_mat, int size){
    for(int i=0; i<size+1; i++){
        coef_mat[col][i] = pow(value, i);
    }
}

bool fitting_format_pointsfile(char* file_name, int size, int degree, comp** y_vector, comp** coef_mat){
	FILE *fp;
    fp = fopen(file_name, "r");
    for(int i=0; i<size; i++){
        double x, y_r, y_i;
        fscanf(fp, "%lf,%lf,%lf\n", &x, &y_r, &y_i);
        
		// make coeficient matrix
        y_vector[i][0] = y_r + y_i * I;
        set_base_fitting(x, i, coef_mat, degree);
    }

    fclose(fp);
	return true;
}
