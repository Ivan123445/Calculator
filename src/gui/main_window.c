#include "../s21_smartcalc.h"

static GtkWidget *create_main_window(void) {
  GtkWidget *window;
  GtkBuilder *builder;
  GError *error = NULL;

  builder = gtk_builder_new();
  if (!gtk_builder_add_from_file(builder, "../src/gui/calc.glade", &error)) {
    g_critical("Не могу загрузить файл: %s", error->message);
    g_error_free(error);
  }
  gtk_builder_connect_signals(builder, NULL);

  window = GTK_WIDGET(gtk_builder_get_object(builder, "Main"));
  if (!window) {
    g_critical("Ошибка при получении виджета окна");
  }
  g_object_unref(builder);

  return window;
}

G_MODULE_EXPORT GtkWidget *create_credit_calc_window(
    GtkButton *button, GtkWidget *credit_calc_window) {
  gtk_widget_show(credit_calc_window);
}

G_MODULE_EXPORT void add_symb_to_str(GtkButton *button, gpointer label) {
  char *str = (char *)gtk_entry_get_text(label);
  if (!strcmp(str, PARSE_ERR_MESSEAGE) || !strcmp(str, RPN_ERR_MESSEAGE) ||
      !strcmp(str, "0")) {
    gtk_entry_buffer_delete_text(gtk_entry_get_buffer(label), 0,
                                 MAX_LENGTH_INPUT);
  }
  char ch = gtk_button_get_label(button)[0];
  GtkEntryBuffer *buf = gtk_entry_get_buffer(label);
  if (ch == 's') {
    gtk_entry_buffer_insert_text(buf, -1, "sqrt(", 5);
  } else if (ch == 'm') {
    gtk_entry_buffer_insert_text(buf, -1, "mod", 3);
  } else {
    gtk_entry_buffer_insert_text(buf, -1, &ch, 1);
  }
}

G_MODULE_EXPORT void clear_str(GtkButton *button, gpointer label) {
  gtk_entry_buffer_delete_text(gtk_entry_get_buffer(label), 0,
                               MAX_LENGTH_INPUT);
}

G_MODULE_EXPORT void clear_last_chr(GtkButton *button, gpointer label) {
  int str_lenght = gtk_entry_buffer_get_length(gtk_entry_get_buffer(label));
  gtk_entry_buffer_delete_text(gtk_entry_get_buffer(label), str_lenght - 1, 1);
}

G_MODULE_EXPORT void calculate(GtkButton *button, gpointer input_grid) {
    GtkEntry *label = (GtkEntry*) gtk_grid_get_child_at(input_grid, 0, 2);
  char *str = (char *)gtk_entry_get_text(label);
  Stack *stack = NULL;
  Stack *rpn = NULL;
  double num;
  char output_str[MAX_LENGTH_INPUT];

  if (strlen(str) && parse_str(str, &stack) == OK) {
    inverse_stack(&stack);
    if (convert_to_rpn(stack, &rpn) == OK) {
      inverse_stack(&rpn);
      if (calc_rpn(rpn, 1, &num) == OK) {
        sprintf(output_str, "%g", num);
      } else {
        sprintf(output_str, CALC_ERR_MESSEAGE);
      }
    } else {
      sprintf(output_str, RPN_ERR_MESSEAGE);
    }
  } else {
    sprintf(output_str, PARSE_ERR_MESSEAGE);
  }

  gtk_entry_set_text(label, output_str);
}

G_MODULE_EXPORT void create_graph(GtkButton *button, gpointer input_grid) {
  GtkWidget *field_x_start = gtk_grid_get_child_at(input_grid, 0, 0);
  GtkWidget *field_x_end = gtk_grid_get_child_at(input_grid, 0, 1);
  GtkWidget *field_y_start = gtk_grid_get_child_at(input_grid, 1, 0);
  GtkWidget *field_y_end = gtk_grid_get_child_at(input_grid, 1, 1);
  GtkWidget *field_expression = gtk_grid_get_child_at(input_grid, 0, 2);

  char *str_x_start = (char *)gtk_entry_get_text(field_x_start);
  char *str_x_end = (char *)gtk_entry_get_text(field_x_end);
  char *str_y_start = (char *)gtk_entry_get_text(field_y_start);
  char *str_y_end = (char *)gtk_entry_get_text(field_y_end);
  char *str_expression = (char *)gtk_entry_get_text(field_expression);

  if (strlen(str_x_start) && strlen(str_x_end) && strlen(str_expression)) {
    int x_start, x_end;
    sscanf(str_x_start, "%d", &x_start);
    sscanf(str_x_end, "%d", &x_end);

    if (create_coordinate_file(str_expression, atoi(str_x_start),
                               atoi(str_x_end), GRAPH_POINTS) == OK) {
      create_graph_image(str_x_start, str_x_end, str_y_start, str_y_end, 5);
      create_graph_window();
    }
  }
}

G_MODULE_EXPORT void enter_calc (GtkButton *button) {
    printf("Here\n");
}

int create_graph_image(char *x_start, char *x_end, char *y_start, char *y_end,
                       double scale) {
  int code = OK;
  char x[40], y[40], plot[70];
  sprintf(x, "set xrange [%s: %s]",
          x_start,  // x start
          x_end);   // x end
  sprintf(y, "set yrange [%s: %s]",
          y_start,  // y start
          y_end);   // y end
  sprintf(plot, "plot \"coordinates.txt\" title \"scaling: %lf\" ps 0.5",
          scale);
  FILE *gnu_plot = popen("gnuplot -persistent", "w");
  if (gnu_plot != NULL) {
    char *commands_gnu_plot[] = {"set terminal png enhanced truecolor",
                                 "set output \"graph.png\"",
                                 "set decimalsign locale",
                                 "set xlabel \"x\"",
                                 "set ylabel \"y\"",
                                 x,
                                 y,
                                 plot,
                                 "set out"};
    int i;

    for (i = 0; i < 9; i++) {
      fprintf(gnu_plot, "%s \n", commands_gnu_plot[i]);
    }
    pclose(gnu_plot);
  } else {
    code = ERROR;
  }
  return code;
}

void create_graph_window() {
  GtkWidget *pic = gtk_image_new_from_file("graph.png");
  if (pic != NULL) {
    GtkWidget *func_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(func_window), "Function graph");
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(func_window), grid);

    gtk_grid_attach(GTK_GRID(grid), pic, 0, 0, 1, 2);

    gtk_widget_show_all(func_window);
  }
}

int main(int argc, char *argv[]) {
  GtkWidget *window;
  GtkCssProvider *provider = gtk_css_provider_new();
  GError *errors;

  gtk_init(&argc, &argv);

  window = create_main_window();
  gtk_css_provider_load_from_path(provider, "common.css", &errors);
    gtk_style_context_add_provider_for_screen(
            gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gtk_widget_show(window);

  gtk_main();
  return 0;
}