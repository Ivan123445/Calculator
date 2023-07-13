#include "test.h"

START_TEST(conv_1) {
  char *str = "5+x\0";
  float x, y;
  int code;

  code = create_coordinate_file(str, 0, 10, 11);

  ck_assert_int_eq(code, OK);
  FILE *coord_file = fopen(NAME_COORDINATE_FILE, "r");
  for (int i = 0; coord_file && i < 10; ++i) {
    fscanf(coord_file, "%f %f\n", &x, &y);
    ck_assert_double_eq(x, i);
    ck_assert_double_eq(y, i + 5);
  }
}
END_TEST

Suite *suite_create_coordinate_file() {
  Suite *suite = suite_create("suite_create_coordinate_file");
  TCase *tcase = tcase_create("case_create_coordinate_file");

  tcase_add_test(tcase, conv_1);

  suite_add_tcase(suite, tcase);
  return suite;
}
