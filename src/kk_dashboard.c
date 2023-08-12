#include <kk_dashboard.h>
#include <kk_css.h>

void start_button_pressed(GtkWidget *widget,
                          gpointer data)
{
}

void activateDashboard(GtkApplication *app,
                       gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *logs_box;
    GtkWidget *button_start;
    GtkWidget *button_stop;
    GtkWidget *button_logs;

    gtk_css();

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Krokodil");
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 500);

    box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_set_name(box, "box");
    g_object_set(box, "margin-bottom", 10, NULL);
    g_object_set(box, "margin-right", 10, NULL);


    button_stop = gtk_button_new_with_label("STOP");
    gtk_widget_set_name(button_stop, "button_stop");
    gtk_container_add(GTK_CONTAINER(box), button_stop);
    g_object_set(button_stop, "margin-right", 5, NULL);
    gtk_widget_set_halign(box, GTK_ALIGN_END);
    gtk_widget_set_valign(box, GTK_ALIGN_END);
    //g_signal_connect(button_stop, "clicked", G_CALLBACK(stop_button_pressed), NULL);
    // g_signal_connect_swapped(button_start, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    
    button_start = gtk_button_new_with_label("START");
    gtk_container_add(GTK_CONTAINER(box), button_start);
    g_signal_connect(button_start, "clicked", G_CALLBACK(start_button_pressed), NULL);
    // g_signal_connect_swapped(button_start, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    //gtk_widget_set_halign(button_start, GTK_ALIGN_END);
    //gtk_widget_set_valign(button_start, GTK_ALIGN_END);
    gtk_widget_set_halign(box, GTK_ALIGN_END);
    gtk_widget_set_valign(box, GTK_ALIGN_END);
    gtk_widget_set_name(button_start, "button_start");

    logs_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_halign(logs_box, GTK_ALIGN_START);
    gtk_widget_set_valign(logs_box, GTK_ALIGN_END);
    gtk_container_add(GTK_CONTAINER(window), logs_box);
    gtk_widget_set_name(logs_box, "logs_box");
    g_object_set(logs_box, "margin-bottom", 10, NULL);
    g_object_set(logs_box, "margin-left", 10, NULL);


    gtk_widget_show_all(window);
}

void *startDashboard()
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.krokodil.dashboard", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activateDashboard), NULL);
    status = g_application_run(G_APPLICATION(app), NULL, NULL);
    g_object_unref(app);
}