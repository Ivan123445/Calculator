#include "s21_smartcalc.h"

static GtkWidget* create_window (void) {
    /* это виджет окна */
    GtkWidget *window;
    /* это тот волшебный объект, который сделает за нас окошко */
    GtkBuilder *builder;
    /* сюда будем складывать ошибки */
    GError* error = NULL;

    /* тут загружаем файл с интерфейсом */
    builder = gtk_builder_new ();
    if (!gtk_builder_add_from_file (builder, "../src/gui/calc.glade", &error))
    {
        /* загрузить файл не удалось */
        g_critical ("Не могу загрузить файл: %s", error->message);
        g_error_free (error);
    }

    /* помните, мы подключали сигналы вручную? теперь это происходит автоматически! */
    gtk_builder_connect_signals (builder, NULL);

    /* получаем виджет окна, чтобы его показать */
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
    if (!window)
    {
        /* что-то не так, наверное, ошиблись в имени */
        g_critical ("Ошибка при получении виджета окна");
    }
    g_object_unref (builder);

    return window;
}

G_MODULE_EXPORT void add_symb_to_str(GtkButton *button, gpointer label) {
    char *str = (char*)gtk_entry_get_text(label);
    if (!strcmp(str, PARSE_ERR_MESSEAGE) || !strcmp(str, RPN_ERR_MESSEAGE) || !strcmp(str, "0")) {
        gtk_entry_buffer_delete_text(gtk_entry_get_buffer(label), 0, MAX_LENGTH_INPUT);
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
    gtk_entry_buffer_delete_text(gtk_entry_get_buffer(label), 0, MAX_LENGTH_INPUT);
}

G_MODULE_EXPORT void clear_last_chr(GtkButton *button, gpointer label) {
    int str_lenght = gtk_entry_buffer_get_length(gtk_entry_get_buffer(label));
    gtk_entry_buffer_delete_text(gtk_entry_get_buffer(label), str_lenght - 1, 1);
}

G_MODULE_EXPORT void calculate(GtkButton *button, gpointer label) {
    char *str = (char*)gtk_entry_get_text(label);
    Stack *stack = NULL;
    Stack *rpn = NULL;
    double num;
    char output_str[MAX_LENGTH_INPUT];

    if (parse_str(str, &stack) == OK) {
        inverse_stack(&stack);
        if (convert_to_rpn(stack, &rpn) == OK) {
            inverse_stack(&rpn);
            if(calc_rpn(rpn, 1, &num) == OK) {
                sprintf(output_str, "%g", num);
            } else {
                sprintf(output_str,CALC_ERR_MESSEAGE);
            }
        } else {
            sprintf(output_str,RPN_ERR_MESSEAGE);
        }
    } else {
        sprintf(output_str,PARSE_ERR_MESSEAGE);
    }

    gtk_entry_set_text(label, output_str);
}

G_MODULE_EXPORT void create_graph (GtkButton *button, gpointer label) {
    char *str = (char*)gtk_entry_get_text(label);
    create_coordinate_file(str, 0, 10, 10);

}


int create_function_image( double scale) {
    int code = OK;
    char x[40], y[40], plot[70];
    sprintf(x, "set xrange [%s: %s]",
            gtk_entry_get_text(GTK_ENTRY(10)),  // x start
            gtk_entry_get_text(GTK_ENTRY(20)));  // x end
    sprintf(y, "set yrange [%s: %s]",
            gtk_entry_get_text(GTK_ENTRY(10)),  // y start
            gtk_entry_get_text(GTK_ENTRY(10)));  // y end
    sprintf(plot, "plot \"function.txt~\" title \"scaling: %lf\" ps 0.5", scale);
    FILE *gnu_plot = popen("gnuplot -persistent", "w");
    if (gnu_plot != NULL) {
        char *commands_gnu_plot[] = {"set terminal png enhanced truecolor",
                                     "set output \"function.png~\"",
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
    GtkWidget *pic = gtk_image_new_from_file("graph.png~");
    if (pic != NULL) {
        GtkWidget *func_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(func_window), "Function graph");
        GtkWidget *grid = gtk_grid_new();
        gtk_container_add(GTK_CONTAINER(func_window), grid);

        gtk_grid_attach(GTK_GRID(grid), pic, 0, 0, 1, 2);

        gtk_widget_show_all(func_window);
    }
}

/* это главная функция нашего приложения, которая будет выполнена первой */
int main (int argc, char *argv[])
{
    /* виджет окна */
    GtkWidget *window;

    /* запускаем GTK+ */
    gtk_init (&argc, &argv);

    /* вызываем нашу функцию для создания окна */
    window = create_window ();
    gtk_widget_show (window);

    /* передаём управление GTK+ */
    gtk_main ();
    return 0;
}