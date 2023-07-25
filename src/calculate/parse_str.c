#include "s21_calculate.h"

void comma_to_point(char *str) {
  for (; str && *str != '\0'; ++str) {
    if (*str == ',') {
      *str = '.';
    }
  }
}

int parse_str(char *str, Stack **result) {
  Stack *stack = NULL;
  comma_to_point(str);
  char *end_str = str + strlen(str);

  for (; str < end_str && (!stack || stack->type != ERR); str++) {
    isddigit(*str) ? pushl(&stack, NUM, scan_decimal((const char **)&str, 0))
                   : 0;

    if (!strchr(OPERATORS_DICTIONARY, *str)) {
      pushl(&stack, ERR, 0);
      break;
    }

    *str == 'x' ? pushl(&stack, X, 0) : 0;
    *str == '(' ? pushl(&stack, O_BRACKETS, 0) : 0;
    *str == ')' ? pushl(&stack, C_BRACKETS, 0) : 0;
    *str == '*' ? pushl(&stack, MULT, 0) : 0;
    *str == '/' ? pushl(&stack, DIV, 0) : 0;
    *str == '^' ? pushl(&stack, POW, 0) : 0;

    if (*str == '+') {
      if (!stack || stack->type == MULT || stack->type == DIV ||
          stack->type == O_BRACKETS) {
        pushl(&stack, U_PLUS, 0);
      } else {
        pushl(&stack, PLUS, 0);
      }
    }
    if (*str == '-') {
      if (!stack || stack->type == MULT || stack->type == DIV ||
          stack->type == O_BRACKETS) {
        pushl(&stack, U_MINUS, 0);
      } else {
        pushl(&stack, MINUS, 0);
      }
    }
    if (*str == 'c') {
      if (strstr(str, "os") == str + 1) {
        pushl(&stack, COS, 0);
      } else {
        pushl(&stack, ERR, 0);
      }
    }

    if (*str == 's') {
      if (strstr(str, "in") == str + 1) {
        pushl(&stack, SIN, 0);
      } else {
        if (strstr(str, "qrt") == str + 1) {
          pushl(&stack, SQRT, 0);
        } else {
          pushl(&stack, ERR, 0);
        }
      }
    }

    if (*str == 't') {
      if (strstr(str, "an") == str + 1) {
        pushl(&stack, TAN, 0);
      } else {
        pushl(&stack, ERR, 0);
      }
    }

    if (*str == 'm') {
      if (strstr(str, "od") == str + 1) {
        pushl(&stack, MOD, 0);
      } else {
        pushl(&stack, ERR, 0);
      }
    }

    if (*str == 'l') {
      if (strstr(str, "n") == str + 1) {
        pushl(&stack, LN, 0);
      } else {
        if (strstr(str, "og") == str + 1) {
          pushl(&stack, LOG, 0);
        } else {
          pushl(&stack, ERR, 0);
        }
      }
    }

    if (*str == 'a') {
      if (strstr(str, "sin") == str + 1) {
        pushl(&stack, ASIN, 0);
      } else {
        if (strstr(str, "cos") == str + 1) {
          pushl(&stack, ACOS, 0);
        } else {
          if (strstr(str, "tan") == str + 1) {
            pushl(&stack, ATAN, 0);
          } else {
            pushl(&stack, ERR, 0);
          }
        }
      }
    }

    if (stack->type >= ACOS && stack->type <= SQRT) {
      str += 3;
    }
    if ((stack->type >= COS && stack->type <= TAN) || stack->type == MOD ||
        stack->type == LOG) {
      str += 2;
    }
    if (stack->type == LN) {
      str += 1;
    }
  }

  if (stack->type != ERR) {
    *result = stack;
  } else {
    clear_stack(&stack);
    *result = NULL;
  }
  return *result ? OK : ERROR;
}
