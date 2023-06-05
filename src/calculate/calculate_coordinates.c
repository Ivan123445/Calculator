#include "s21_calculate.h"

int calculate_coordinates(char *str, int start, int end, int steps, double **result) {
    int status = OK;
    Stack *stack = NULL;
    Stack *rpn = NULL;
    *result = calloc(steps, sizeof(double));

    status = parse_str(str, &stack);
    if (status == OK) {
        inverse_stack(&stack);
        status = convert_to_rpn(stack, &rpn);
        if (status == OK) {
            inverse_stack(&rpn);
            double step = (double) (end - start) / (steps - 1);
            double x = (double) start;
            double y;
            for (int i = 0; status == OK && i < steps; ++i) {
                Stack *temp_rpn = NULL;
                copy_stack(&temp_rpn, rpn);
                status = calc_rpn(temp_rpn, x, &y);
                (*result)[i] = y;
                x += step;
            }
        }
    }

    return status;
}
