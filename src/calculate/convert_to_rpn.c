#include "s21_calculate.h"

int get_priority(Stack tok) {
    int res = 0;
    if (tok.type == PLUS || tok.type == MINUS) {
        res = 1;
    }
    if (tok.type == MULT || tok.type == DIV || tok.type == MOD) {
        res = 2;
    }
    if (tok.type == POW) {
        res = 3;
    }
    if (tok.type >= U_PLUS) {
        res = 4;
    }

    return res;
}

int convert_to_rpn(Stack *tokens, Stack **rpn) {
    Stack *res = NULL, *stack = NULL;
    Stack tok = pop(&tokens);

    for (; tok.type != END && (!res || res->type != ERR); tok = pop(&tokens)) {
        if (tok.type == NUM || tok.type == X) {
            push(&res, tok);
        }
        if (tok.type == O_BRACKETS || tok.type >= COS) {
            push(&stack, tok);
        }
        if (tok.type >= PLUS && tok.type <= U_MINUS) {
            while (stack && (get_priority(*stack) >= get_priority(tok) ||
                    (get_priority(*stack) == get_priority(tok) && stack->type >= POW && stack->type <= U_MINUS))) {
                push(&res, pop(&stack));
            }
            push(&stack, tok);
        }
        if (tok.type == C_BRACKETS) {
            while (stack && stack->type != O_BRACKETS) {
                push(&res, pop(&stack));
            }
            if (stack && stack->type == O_BRACKETS) {
                pop(&stack);
                if (stack && stack->type >= COS) {
                    push(&res, pop(&stack));
                }
            } else {
               res ? res->type = ERR : 0;
            }
        }
    }

    tok = pop(&stack);
    for (; tok.type != END && res && res->type != ERR; tok = pop(&stack)){
        if (tok.type == O_BRACKETS || tok.type == C_BRACKETS) {
            res->type = ERR;
        } else {
            push(&res, tok);
        }
    }
    if (!res || res->type == ERR) {
        clear_stack(&res);
        clear_stack(&stack);
    }

    *rpn = res;
    return res && res->type != ERR ? OK : ERROR;
}