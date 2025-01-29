/*
複素数の行列に関する計算
*/

#ifndef comp_calc
#define comp_calc

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "setting.h"

// calculation functions
comp** calc_multipl_mat(int ans_col_size, int middle_size, int ans_row_size, comp** multcand, comp** multpler);
comp** calc_transp_mat(int col_size, int row_size, comp** mat);
comp** calc_inverse_mat(int size, comp** mat);

#endif
