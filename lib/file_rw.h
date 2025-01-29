/*
ファイルの読み書き、データのプロット。
ファイルと読み始めの行を指定すると、128個分のデータを読み込み、
計算に必要な形にフォーマットする。
*/

#ifndef file_rw
#define file_rw

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "setting.h"

// get(format) matrix from csv file
comp** get_matrix(char* file_name, int size_col, int size_row);
// show
void show_matrix(int size_col, int size_row, comp** mat);
void double_show_matrix(int size_col, int size_row, double** mat);

bool fourier_format_pointsfile(char* file_name, int size_point, int size_degree, comp** y_vector, comp** coef_mat);
bool fitting_format_pointsfile(char* file_name, int size_point, int size_degree, double** y_vector, double** coef_mat);

#endif
