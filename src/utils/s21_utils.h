#ifndef C7_SMARTCALC_V1_0_1_S21_UTILS_H
#define C7_SMARTCALC_V1_0_1_S21_UTILS_H

#include "string.h"

#include <malloc.h>
#include <stdbool.h>
#include <math.h>

#define OK 0
#define ERROR (-1)

#define DEFAULT_STACK {NULL, 0, 0}
#define ASCII_NUM_OFFSET 48

typedef enum {
    END,
    ERR,
    NUM,
    O_BRACKETS,
    C_BRACKETS,

    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD,
    EXP,
    U_PLUS,
    U_MINUS,

    COS,
    SIN,
    TAN,
    ACOS,
    ASIN,
    ATAN,
    SQRT,
    LN,
    LOG
} Type;

typedef struct {
    struct Stack *prev;
    Type type;
    double value;
} Stack;

void pushl (Stack **head, Type type, double value);
void push (Stack **head, Stack elem);
Stack pop (Stack **head);
void clear_stack(Stack **head);
void inverse_stack(Stack **head);

double scan_decimal(const char **str, int width);
bool isddigit(char num);

#endif //C7_SMARTCALC_V1_0_1_S21_UTILS_H
