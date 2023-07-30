#include "test.h"

int main() {
  Suite* suites[] = {parser_suite(),
                     convert_to_rpn_suite(),
                     suite_calc_rpn(),
                     suite_calculate_coordinates(),
                     suite_create_coordinate_file(),
                     NULL};

  for (int i = 0; i < 5; ++i) {
    SRunner* srunner = srunner_create(suites[i]);
    srunner_run_all(srunner, CK_NORMAL);
    srunner_free(srunner);
  }

  return 0;
}