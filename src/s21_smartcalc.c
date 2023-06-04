#include "s21_smartcalc.h"


/* создание окна в этот раз мы вынесли в отдельную функцию */
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
    char ch = gtk_button_get_label(button)[0];
    if (strchr(INP_DICTION, ch)) {
        gtk_entry_buffer_insert_text(gtk_entry_get_buffer(label), -1, &ch, 1);
    } else {
        printf("Wrong char\n");
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
    printf("%s\n", str);

    Stack *stack = parse_str(str);
    inverse_stack(&stack);
    Stack *rpn = convert_to_rpn(stack);
    inverse_stack(&rpn);
    printf("Res:%f\n", calc_rpn(rpn, 11));

//    gtk_entry_set_text(label, itoa())
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