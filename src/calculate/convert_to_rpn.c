#include "s21_calculate.h"

int get_priority(Stack tok) {
    int res = 0;
    if (tok.type == PLUS || tok.type == MINUS) {
        res = 1;
    }
    if (tok.type == MULT || tok.type == DIV || tok.type == MOD) {
        res = 2;
    }
    if (tok.type == EXP) {
        res = 3;
    }
    if (tok.type >= U_PLUS) {
        res = 4;
    }

    return res;
}

Stack* convert_to_rpn(Stack *tokens) {
    Stack *rpn = NULL, *stack = NULL;
    Stack tok = pop(&tokens);
    if (tok.type == END) {
        tok = pop(&tokens);
    }

    for (; tok.type != END && tok.type != ERR; tok = pop(&tokens)) {
        if (tok.type == NUM) {
            push(&rpn, tok.type, tok.value);
        }
        if (tok.type == O_BRACKETS || tok.type >= COS) {
            push(&stack, tok.type, tok.value);
        }
        if (tok.type >= PLUS && tok.type <= U_MINUS) {
            while (stack && (get_priority(*stack) >= get_priority(tok) ||
                    (get_priority(*stack) == get_priority(tok) && stack->type >= EXP && stack->type <= U_MINUS))) {
                Stack temp = pop(&stack);
                push(&rpn, temp.type, temp.value);
            }
            push(&stack, tok.type, tok.value);
        }
        if (tok.type == C_BRACKETS) {
            while (stack && stack->type != O_BRACKETS && stack->type != ERR) {
                Stack temp = pop(&stack);
                push(&rpn, temp.type, temp.value);
            }
            pop(&stack);
            if (stack && stack->type >= COS) {
                Stack temp = pop(&stack);
                push(&rpn, temp.type, temp.value);
            }
        }
    }

    tok = pop(&stack);
    if (tok.type == O_BRACKETS || tok.type == C_BRACKETS) {
        clear_stack(&rpn);
        clear_stack(&stack);
        return NULL;
    }
    for (; tok.type != END && tok.type != ERR; tok = pop(&stack)){
        push(&rpn, tok.type, tok.value);
    }

    return rpn;
}