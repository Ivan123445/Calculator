#include "s21_utils.h"

void push(Stack **head, Stack elem) { pushl(head, elem.type, elem.value); }

void pushl(Stack **head, Type type, double value) {
  Stack *prev = *head;
  *head = calloc(1, sizeof(Stack));
  (*head)->type = type;
  (*head)->value = value;
  (*head)->prev = prev;
}

Stack pop(Stack **head) {
  Stack last = DEFAULT_STACK;
  if (head && *head) {
    Stack *new_head = (*head)->prev;
    last.type = (*head)->type;
    last.value = (*head)->value;
    free(*head);
    *head = new_head;
  }
  return last;
}

void clear_stack(Stack **head) {
  if (head && (*head)) {
    while ((*head)->prev) {
      Stack *temp = (*head)->prev;
      free((*head));
      (*head) = temp;
    }
    free((*head));
  }
}

void copy_stack(Stack **dest, Stack *src) {
  while (src) {
    push(dest, *src);
    src = src->prev;
  }
  inverse_stack(dest);
}

void inverse_stack(Stack **head) {
  if (!(*head)) {
    return;
  }
  Stack *new_stack = NULL;
  while ((*head)->prev) {
    push(&new_stack, pop(head));
  }
  push(&new_stack, pop(head));

  (*head) = new_stack;
}
