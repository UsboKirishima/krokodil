#include <kk_ui.h>

void login_button_pressed(GtkWidget *widget,
                          gpointer data)
{
    g_print(gtk_entry_get_text(data));
}

void activate(GtkApplication *app,
              gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box;
    GtkWidget *key_box;
    GtkWidget *key_label;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
    gtk_container_add(GTK_CONTAINER(window), box);

    key_label = gtk_label_new("Enter your key:");
    gtk_container_add(GTK_CONTAINER(box), key_label);
    gtk_widget_set_halign(key_label, GTK_ALIGN_START);

    key_box = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(key_box), 0);
    gtk_container_add(GTK_CONTAINER(box), key_box);

    button = gtk_button_new_with_label("Login");
    gtk_container_add(GTK_CONTAINER(box), button);
    g_signal_connect(button, "clicked", G_CALLBACK(login_button_pressed), key_box);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);

    // Margins
    g_object_set(key_box, "margin-bottom", 20, NULL);
    g_object_set(key_label, "margin-bottom", 5, NULL);

    gtk_widget_show_all(window);
}

void *startUI()
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.krokodil", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), NULL, NULL);
    g_object_unref(app);
}