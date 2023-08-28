#include <gtk/gtk.h>

static void
print_hello(GtkWidget *widget,
            gpointer data)
{
    g_print("Hello World\n");
}

char *startId()
{
    GtkBuilder *builder;
    GObject *window;
    GObject *button;
    GObject *entry;
    GObject *label;
    GError *error = NULL;

    gtk_init(NULL, NULL);

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "src/kk_id.ui", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    window = gtk_builder_get_object(builder, "window");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    label = gtk_builder_get_object(builder, "label");

    entry = gtk_builder_get_object(builder, "entry");
    g_object_set(entry, "margin-bottom", 20, NULL);

    button = gtk_builder_get_object(builder, "quit");
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();

    return;
}