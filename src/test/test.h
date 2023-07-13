#ifndef C7_SMARTCALC_V1_0_1_TEST_H
#define C7_SMARTCALC_V1_0_1_TEST_H

#include <check.h>

#include "../calculate/s21_calculate.h"
#include "../s21_smartcalc.h"
#include "../utils/s21_utils.h"

#define EPS 1e-07
#define ACCURACY 1e-07

Suite *parser_suite();
Suite *convert_to_rpn_suite();
Suite *suite_calc_rpn();
Suite *suite_calculate_coordinates();
Suite *suite_create_coordinate_file();

#endif  // C7_SMARTCALC_V1_0_1_TEST_H
