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

    for (; tok.type != END && (!rpn || rpn->type != ERR); tok = pop(&tokens)) {
        if (tok.type == NUM) {
            push(&rpn, tok);
        }
        if (tok.type == O_BRACKETS || tok.type >= COS) {
            push(&stack, tok);
        }
        if (tok.type >= PLUS && tok.type <= U_MINUS) {
            while (stack && (get_priority(*stack) >= get_priority(tok) ||
                    (get_priority(*stack) == get_priority(tok) && stack->type >= EXP && stack->type <= U_MINUS))) {
                push(&rpn, pop(&stack));
            }
            push(&stack, tok);
        }
        if (tok.type == C_BRACKETS) {
            while (stack && stack->type != O_BRACKETS) {
                push(&rpn, pop(&stack));
            }
            if (stack && stack->type == O_BRACKETS) {
                pop(&stack);
                if (stack && stack->type >= COS) {
                    push(&rpn, pop(&stack));
                }
            } else {
                rpn->type = ERR;
            }
        }
    }

    tok = pop(&stack);
    for (; tok.type != END && rpn->type != ERR; tok = pop(&stack)){
        if (tok.type == O_BRACKETS || tok.type == C_BRACKETS) {
            rpn->type = ERR;
        } else {
            push(&rpn, tok);
        }
    }
    if (rpn->type == ERR) {
        clear_stack(&rpn);
        clear_stack(&stack);
        rpn = NULL;
    }

    return rpn;
}