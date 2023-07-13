#ifndef C7_SMARTCALC_V1_0_1_S21_CALCULATE_H
#define C7_SMARTCALC_V1_0_1_S21_CALCULATE_H

#include "../utils/s21_utils.h"

#define DICTION "1234567890+-*/^.,()asctlnsmx"
#define NAME_COORDINATE_FILE "coordinates.txt"

int parse_str(char *str, Stack **result);
int convert_to_rpn(Stack *stack, Stack **rpn);
int calc_rpn(Stack *rpn, double x, double *result);

int calculate_coordinates(char *str, int start, int end, int steps,
                          double **res);
int create_coordinate_file(char *str, int x_start, int x_end, int step);

#endif  // C7_SMARTCALC_V1_0_1_S21_CALCULATE_H
