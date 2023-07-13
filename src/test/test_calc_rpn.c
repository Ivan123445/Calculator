#include "test.h"

START_TEST(conv_1) {
  Stack *stack = NULL, *rpn = NULL;
  char *str = "5+2*8-2/2+2^2+2mod1+2e2+2e-1\0";
  int code;
  double res;

  parse_str(str, &stack);
  inverse_stack(&stack);
  convert_to_rpn(stack, &rpn);
  inverse_stack(&rpn);
  code = calc_rpn(rpn, 0, &res);

  ck_assert_int_eq(code, OK);
  ck_assert_double_eq(res, 224.2);
}
END_TEST

START_TEST(conv_2) {
  Stack *stack = NULL, *rpn = NULL;
  char *str =
      "cos(0)+sin(0)+acos(1)+asin(0)+log(10)+ln(1)+tan(0)+atan(0)+(2)+sqrt(4)+x"
      "\0";
  int code;
  double res;

  parse_str(str, &stack);
  inverse_stack(&stack);
  convert_to_rpn(stack, &rpn);
  inverse_stack(&rpn);
  code = calc_rpn(rpn, 0, &res);

  ck_assert_int_eq(code, OK);
  ck_assert_double_eq(res, 6);
}
END_TEST

START_TEST(conv_3) {
  Stack *stack = NULL, *rpn = NULL;
  char *str = "+2+(-2)\0";
  int code;
  double res;

  parse_str(str, &stack);
  inverse_stack(&stack);
  convert_to_rpn(stack, &rpn);
  inverse_stack(&rpn);
  code = calc_rpn(rpn, 0, &res);

  ck_assert_int_eq(code, OK);
  ck_assert_double_eq(res, 0);
}
END_TEST

START_TEST(conv_4) {
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

START_TEST(conv_5) {
  Stack *stack = NULL, *rpn = NULL;
  char *str = "2^2+)3*8/6\0";

  parse_str(str, &stack);
  inverse_stack(&stack);
  int code = convert_to_rpn(stack, &rpn);

  ck_assert_int_eq(code, ERROR);
  ck_assert_ptr_null(rpn);

  clear_stack(&rpn);
}

Suite *suite_calc_rpn() {
  Suite *suite = suite_create("suite_calc_rpn");
  TCase *tcase = tcase_create("calc_rpn_case");

  tcase_add_test(tcase, conv_1);
  tcase_add_test(tcase, conv_2);
  tcase_add_test(tcase, conv_3);
  tcase_add_test(tcase, conv_4);
  tcase_add_test(tcase, conv_5);

  suite_add_tcase(suite, tcase);
  return suite;
}
