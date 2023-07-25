#include "test.h"

// void print_stack(Stack *stack) {
//     if (stack) {
//         while (stack->prev) {
//             printf("Type:%d  Value:%f\n", stack->type, stack->value);
//             stack = stack->prev;
//         }
//         printf("Type:%d  Value:%f\n", stack->type, stack->value);
//     } else {
//         printf("Stack is empty\n");
//     }
// }

START_TEST(parser_1) {
  int size = 7;
  const Type tokens[] = {SIN, O_BRACKETS, COS,       O_BRACKETS,
                         X,   C_BRACKETS, C_BRACKETS};
  Stack *res = NULL;
  char *str = "sin(cos(x))";
  int code = parse_str(str, &res);
  inverse_stack(&res);

  ck_assert_int_eq(code, OK);
  for (int i = 0; i < size; ++i) {
    Stack elem = pop(&res);

    ck_assert_int_eq(elem.type, tokens[i]);
  }

  clear_stack(&res);
}
END_TEST

START_TEST(parser_2) {
  Stack *res = NULL;
  char *str = "ln-+coc";
  int code = parse_str(str, &res);
  ck_assert_int_eq(code, ERROR);
  ck_assert_ptr_eq(res, NULL);
}
END_TEST

START_TEST(parser_3) {
  int size = 14;
  const Type tokens[] = {ASIN, O_BRACKETS, ATAN,       O_BRACKETS, X,
                         MULT, SQRT,       O_BRACKETS, LOG,        O_BRACKETS,
                         X,    C_BRACKETS, C_BRACKETS, C_BRACKETS};
  Stack *res = NULL;
  char *str = "asin(atan(x*sqrt(log(x)))";
  int code = parse_str(str, &res);
  inverse_stack(&res);

  ck_assert_int_eq(code, OK);
  for (int i = 0; i < size; ++i) {
    Stack elem = pop(&res);

    ck_assert_int_eq(elem.type, tokens[i]);
  }
  clear_stack(&res);
}
END_TEST

START_TEST(parser_4) {
  Stack *res = NULL;
  char *str = "tan(acos(a*sin(cos(x)))";
  int code = parse_str(str, &res);

  ck_assert_int_eq(code, ERROR);
  ck_assert_ptr_eq(res, NULL);
}
END_TEST

START_TEST(parser_5) {
  Stack *res = NULL;
  char *str = "+2.5mod-3mob";
  int code = parse_str(str, &res);

  ck_assert_int_eq(code, ERROR);
  ck_assert_ptr_eq(res, NULL);
}
END_TEST

START_TEST(parser_6) {
  Stack *res = NULL;
  char *str = "-2.5qom-3mob";
  int code = parse_str(str, &res);

  ck_assert_int_eq(code, ERROR);
  ck_assert_ptr_eq(res, NULL);
}
END_TEST

START_TEST(parser_7) {
  Stack *res = NULL;
  const Type tokens[] = {NUM, PLUS, NUM};
  char *str = "5+5";
  int size = 3;
  int code = parse_str(str, &res);

  ck_assert_int_eq(code, OK);
  for (int i = 0; i < size; ++i) {
    Stack elem = pop(&res);

    ck_assert_int_eq(elem.type, tokens[i]);
  }
  clear_stack(&res);
}
END_TEST

Suite *parser_suite() {
  Suite *suite = suite_create("parser_suite");
  TCase *tcase = tcase_create("parser_case");

  tcase_add_test(tcase, parser_1);
  tcase_add_test(tcase, parser_2);
  tcase_add_test(tcase, parser_3);
  tcase_add_test(tcase, parser_4);
  tcase_add_test(tcase, parser_5);
  tcase_add_test(tcase, parser_6);
  tcase_add_test(tcase, parser_7);

  suite_add_tcase(suite, tcase);
  return suite;
}