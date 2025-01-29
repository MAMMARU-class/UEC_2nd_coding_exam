/*
doubleの行列に関する計算
*/

#ifndef double_calc
#define double_calc

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "setting.h"

// calculation functions
double** double_calc_multipl_mat(int ans_col_size, int middle_size, int ans_row_size, double** multcand, double** multpler);
double** double_calc_transp_mat(int col_size, int row_size, double** mat);
double** double_calc_inverse_mat(int size, double** mat);

#endif
