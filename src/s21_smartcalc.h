#ifndef C7_SMARTCALC_V1_0_1_S21_SMARTCALC_H
#define C7_SMARTCALC_V1_0_1_S21_SMARTCALC_H

#include <gtk/gtk.h>
#include <stdlib.h>

#include "calculate/s21_calculate.h"
#include "utils/s21_utils.h"

#define MAX_LENGTH_INPUT 255
#define GRAPH_POINTS 1e3
#define DICTION "1234567890+-*/^.,()asctlnsm"
#define PARSE_ERR_MESSEAGE "Wrong symb"
#define RPN_ERR_MESSEAGE "Wrong expression"
#define CALC_ERR_MESSEAGE "Wrong expression"

G_MODULE_EXPORT void create_graph(GtkButton *button, gpointer label);
int create_graph_image(char *x_start, char *x_end, char *y_start, char *y_end,
                       double scale);
void create_graph_window();

#endif  // C7_SMARTCALC_V1_0_1_S21_SMARTCALC_H
