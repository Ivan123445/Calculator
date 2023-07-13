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
//
// #include "../s21_smartcalc.h"
//
// void print_stack(Stack *stack) {
//  if (stack) {
//    while (stack->prev) {
//      printf("Type:%d  Value:%f\n", stack->type, stack->value);
//      stack = stack->prev;
//    }
//    printf("Type:%d  Value:%f\n", stack->type, stack->value);
//  } else {
//    printf("Stack is empty\n");
//  }
//}
//
// int main() {
//     int code = create_coordinate_file("5+x", 0, 10, 11);
//
//   return 0;
// }