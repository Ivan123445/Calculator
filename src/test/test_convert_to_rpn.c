#include "test.h"

START_TEST(conv_1) {
  int size = 3;
  const Type tokens[] = {X, COS, SIN};
  Stack *stack = NULL, *rpn = NULL;
  char *str = "sin(cos(x))\0";

  parse_str(str, &stack);
  inverse_stack(&stack);
  int code = convert_to_rpn(stack, &rpn);
  inverse_stack(&rpn);

  ck_assert_int_eq(code, OK);
  for (int i = 0; i < size; ++i) {
    Stack elem = pop(&rpn);

    ck_assert_int_eq(elem.type, tokens[i]);
  }

  clear_stack(&rpn);
}
END_TEST

START_TEST(conv_2) {
  int size = 3;
  const Type tokens[] = {NUM, NUM, NUM, NUM, MULT, DIV, PLUS};
  Stack *stack = NULL, *rpn = NULL;
  char *str = "2+3*8/6\0";

  parse_str(str, &stack);
  inverse_stack(&stack);
  int code = convert_to_rpn(stack, &rpn);
  inverse_stack(&rpn);

  ck_assert_int_eq(code, OK);
  for (int i = 0; i < size; ++i) {
    Stack elem = pop(&rpn);

    ck_assert_int_eq(elem.type, tokens[i]);
  }

  clear_stack(&rpn);
}
END_TEST

START_TEST(conv_3) {
  Stack *stack = NULL, *rpn = NULL;
  char *str = "2^2+)3*8/6\0";

  parse_str(str, &stack);
  inverse_stack(&stack);
  int code = convert_to_rpn(stack, &rpn);

  ck_assert_int_eq(code, ERROR);
  ck_assert_ptr_null(rpn);

  clear_stack(&rpn);
}

Suite *convert_to_rpn_suite() {
  Suite *suite = suite_create("convert_to_rpn_suite");
  TCase *tcase = tcase_create("convert_to_rpn_case");

  tcase_add_test(tcase, conv_1);
  tcase_add_test(tcase, conv_2);
  tcase_add_test(tcase, conv_3);

  suite_add_tcase(suite, tcase);
  return suite;
}