#include "s21_calculate.h"

Stack* parse_str(char const *str) {
    Stack *stack = NULL;
    push(&stack, END, 0);

    for (; *str != '\0' && stack->type != ERR; str++) {
        !strchr(DICTION, *str) ? push(&stack, ERR, 0) : 0;

        isddigit(*str) ? push(&stack, NUM, scan_decimal(&str, MAX_NUM_LENGTH)) : 0;

        *str == '(' ? push(&stack, O_BRACKETS, 0) : 0;
        *str == ')' ? push(&stack, C_BRACKETS, 0) : 0;
        *str == '*' ? push(&stack, MULT, 0) : 0;
        *str == '/' ? push(&stack, DIV, 0) : 0;
        *str == '^' ? push(&stack, EXP, 0) : 0;

        if (*str == '+') {
            if (stack->type == END || stack->type == MULT || stack->type == DIV) {
                push(&stack, U_PLUS, 0);
            } else {
                push(&stack, PLUS, 0);
            }

        }
        if (*str == '-') {
            if (stack->type == END || stack->type == MULT || stack->type == DIV) {
                push(&stack, U_MINUS, 0);
            } else {
                push(&stack, MINUS, 0);
            }

        }
        if (*str == 'c') {
            if (strstr(str, "os") == str + 1) {
                push(&stack, COS, 0);
                str += 2;
            } else {
                push(&stack, ERR, 0);
            }
        }

        if (*str == 's') {
            if (strstr(str, "in") == str + 1) {
                push(&stack, SIN, 0);
                str += 2;
            } else {
                if (strstr(str, "qrt") == str + 1) {
                    push(&stack, SQRT, 0);
                    str += 3;
                } else {
                    push(&stack, ERR, 0);
                }
            }
        }

        if (*str == 't') {
            if (strstr(str, "an") == str + 1) {
                push(&stack, TAN, 0);
                str += 2;
            } else {
                push(&stack, ERR, 0);
            }
        }

        if (*str == 'm') {
            if (strstr(str, "od") == str + 1) {
                push(&stack, MOD, 0);
                str += 2;
            } else {
                push(&stack, ERR, 0);
            }
        }

        if (*str == 'l') {
            if (strstr(str, "n") == str + 1) {
                push(&stack, LN, 0);
                str += 2;
            } else {
                if (strstr(str, "OG") == str + 1) {
                    push(&stack, LOG, 0);
                    str += 3;
                } else {
                    push(&stack, ERR, 0);
                }
            }
        }

        if (*str == 'a') {
            if (strstr(str, "sin") == str + 1) {
                push(&stack, ASIN, 0);
                str += 2;
            } else {
                if (strstr(str, "cos") == str + 1) {
                    push(&stack, ACOS, 0);
                    str += 3;
                } else {
                    if (strstr(str, "tan") == str + 1) {
                        push(&stack, ATAN, 0);
                        str += 3;
                    }
                    push(&stack, ERR, 0);
                }
            }
        }

    }

    return stack;
}
