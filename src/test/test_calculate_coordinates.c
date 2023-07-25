#include "test.h"

START_TEST(conv_1) {
  char *str = "5+x\0";
  int code;
  double *res;

  code = calculate_coordinates(str, 0, 10, 11, &res);

  ck_assert_int_eq(code, OK);
  for (int i = 0; i < 10; ++i) {
    ck_assert_double_eq(res[i], 5 + i);
  }
  free(res);
}
END_TEST

Suite *suite_calculate_coordinates() {
  Suite *suite = suite_create("suite_calculate_coordinates");
  TCase *tcase = tcase_create("calculate_coordinates_case");

  tcase_add_test(tcase, conv_1);

  suite_add_tcase(suite, tcase);
  return suite;
}
