#include "s21_calculate.h"

int calc_bin_op(Stack **stack, Type type) {
  Stack first_op = pop(stack);
  Stack second_op = pop(stack);
  double res;
  int status = OK;
  if (first_op.type != END && second_op.type != END) {
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
        res = fmod(second_op.value, first_op.value);
        break;
      case POW:
        res = pow(second_op.value, first_op.value);
        break;
      default:
        status = ERROR;
        break;
    }
  } else {
    status = ERROR;
  }
  pushl(stack, NUM, res);
  return status;
}

int calc_un_op(Stack **stack, Type type) {
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
      res = acos(op.value);
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

int calc_rpn(Stack *rpn, double x, double *result) {
  if (!rpn) {
    return 0;
  }
  Stack tok = pop(&rpn);
  Stack *stack = NULL;
  int status = OK;
  int end_rpn_flag = OK;
  for (; end_rpn_flag == OK && status == OK; tok = pop(&rpn)) {
    if (tok.type == NUM) {  // num
      push(&stack, tok);
    } else if (tok.type == X) {
      pushl(&stack, NUM, x);
    } else if (tok.type >= U_PLUS) {  // unary op
      if (stack && stack->type == NUM) {
        status = calc_un_op(&stack, tok.type);
      }
    } else {  // binary op
      status = calc_bin_op(&stack, tok.type);
    }
    if (!rpn) {
      end_rpn_flag = ERROR;
    }
  }

  tok = pop(&stack);
  *result = tok.value;
  return status;
}
