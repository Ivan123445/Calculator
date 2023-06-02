#include "s21_calculate.h"

int calc_bin_op (Stack **stack, Type type) {
    Stack first_op = pop(stack);
    Stack second_op = pop(stack);
    double res;
    int status = OK;
    switch (type) {
        case PLUS:
            res = second_op.value + first_op.value;
            break;
        case MINUS:
            res = second_op.value - first_op.value;
            break;
        case MULT:
            res = second_op.value * first_op.value;
            break;
        case DIV:
            res = second_op.value / first_op.value;
            break;
        case MOD:
            res = second_op.value / first_op.value;
            break;  // TODO fix MOD
        case POW:
            res = pow(second_op.value, first_op.value);
            break;
        default:
            status = ERROR;
            break;
    }
    pushl(stack, NUM, res);
    return status;
}

int calc_un_op (Stack **stack, Type type) {
    int status = OK;
    Stack op = pop(stack);
    double res;
    switch (type) {
        case U_PLUS:
            res = op.value;
            break;
        case U_MINUS:
            res = op.value * -1;
            break;
        case COS:
            res = cos(op.value);
            break;
        case SIN:
            res = sin(op.value);
            break;
        case TAN:
            res = tan(op.value);
            break;
        case ACOS:
            res =  acos(op.value);
            break;
        case ASIN:
            res = asin(op.value);
            break;
        case ATAN:
            res = atan(op.value);
            break;
        case SQRT:
            res = sqrt(op.value);
            break;
        case LN:
            res = log(op.value);
            break;
        case LOG:
            res = log10(op.value);
            break;
        default:
            status = ERROR;
            break;
    }
    pushl(stack, NUM, res);
    return status;
}

double calc_rpn(Stack *rpn, double x) {
    Stack tok = pop(&rpn);
    Stack *stack = NULL;
    int flag = OK;
    for (; flag == OK; tok = pop(&rpn)) {
        if (tok.type == NUM) {  // num
            push(&stack, tok);
        } else if (tok.type == X) {
            pushl(&stack, NUM, x);
        } else if (tok.type >= U_PLUS) {  // unary op
            if (stack && stack->type == NUM) {
                flag = calc_un_op(&stack, tok.type);
            }
        } else {  // binary op
            flag = calc_bin_op(&stack, tok.type);
        }
        if (!rpn) {
            flag = ERROR;
        }
    }

    tok = pop(&stack);
    return tok.value;
}
