#include "../s21_smartcalc.h"

G_MODULE_EXPORT void calculate_deposit(GtkButton *button, gpointer input_grid) {
  GtkWidget *sum = gtk_grid_get_child_at(input_grid, 0, 0);
  GtkWidget *result = gtk_grid_get_child_at(input_grid, 1, 0);
  GtkWidget *interest_rate = gtk_grid_get_child_at(input_grid, 0, 1);

  char *str_sum = (char *)gtk_entry_get_text(GTK_ENTRY(sum));
  char *str_interest_rate =
      (char *)gtk_entry_get_text(GTK_ENTRY(interest_rate));

  if (strlen(str_sum) && strlen(str_interest_rate)) {
    float f_sum, f_interest_rate;
    char str_result[30];
    sscanf(str_sum, "%f", &f_sum);
    sscanf(str_interest_rate, "%f", &f_interest_rate);

    sprintf(str_result, "%f", f_sum * f_interest_rate / 100);
    gtk_entry_set_text(GTK_ENTRY(result), str_result);
  }
}
