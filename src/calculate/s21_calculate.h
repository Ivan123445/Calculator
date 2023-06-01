#ifndef C7_SMARTCALC_V1_0_1_S21_CALCULATE_H
#define C7_SMARTCALC_V1_0_1_S21_CALCULATE_H

#include "../utils/s21_utils.h"

#define MAX_NUM_LENGTH 15
#define DICTION "1234567890+-*/^.()asctlnsm"

Stack* parse_str(char const *str);
Stack* convert_to_rpn(Stack *stack);

#endif //C7_SMARTCALC_V1_0_1_S21_CALCULATE_H
