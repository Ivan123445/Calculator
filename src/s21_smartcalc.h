#ifndef C7_SMARTCALC_V1_0_1_S21_SMARTCALC_H
#define C7_SMARTCALC_V1_0_1_S21_SMARTCALC_H

#include <gtk/gtk.h>
#include <stdlib.h>

#include "calculate/s21_calculate.h"
#include "utils/s21_utils.h"

#define MAX_LENGTH_INPUT 255
#define PARSE_ERR_MESSEAGE "Wrong symb"
#define RPN_ERR_MESSEAGE "Wrong expression"
#define CALC_ERR_MESSEAGE "Wrong expression"

G_MODULE_EXPORT void create_graph (GtkButton *button, gpointer label);

#endif //C7_SMARTCALC_V1_0_1_S21_SMARTCALC_H
