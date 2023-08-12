#include <kk_dashboard.h>
#include <kk_css.h>

typedef struct attack
{
    bool mass_channel;
} t_attack;

bool mass_channel_enabled = false;


void start_button_pressed(GtkWidget *widget,
                          gpointer data)
{
    mass_channel_enabled = gtk_switch_get_state(data);
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
    GtkWidget *mass_channel_label;
    GtkWidget *mass_channel_name_entry;
    GtkWidget *mass_channel_count_spin;
    GtkWidget *mass_channel_type_combobox;
    GtkWidget *mass_channel_enable_switch;

    GtkAdjustment *adj;

    gtk_css();

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Krokodil");
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 500);

    box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_set_name(box, "box");
    g_object_set(box, "margin-top", 10, NULL);
    g_object_set(box, "margin-left", 10, NULL);
    gtk_widget_set_halign(box, GTK_ALIGN_START);
    gtk_widget_set_valign(box, GTK_ALIGN_START);

    mass_channel_label = gtk_label_new("MASS CHANNEL");
    gtk_container_add(GTK_CONTAINER(box), mass_channel_label);
    gtk_widget_set_halign(mass_channel_label, GTK_ALIGN_CENTER);

    mass_channel_name_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(mass_channel_name_entry), 0);
    gtk_container_add(GTK_CONTAINER(box), mass_channel_name_entry);
    g_object_set(mass_channel_name_entry, "margin-left", 10, NULL);
    gtk_entry_set_text(mass_channel_name_entry, "channel-name");

    adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 1.0, 200.0, 1.0,
                                              5.0, 0.0);
    mass_channel_count_spin = gtk_spin_button_new(adj, 0, 0);
    gtk_container_add(GTK_CONTAINER(box), mass_channel_count_spin);
    g_object_set(mass_channel_count_spin, "margin-left", 5, NULL);
    g_object_set(mass_channel_count_spin, "margin-left", 5, NULL);

    mass_channel_type_combobox = gtk_combo_box_text_new();
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(mass_channel_type_combobox), NULL, "Text");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(mass_channel_type_combobox), NULL, "Voice");
    gtk_combo_box_set_active(GTK_COMBO_BOX(mass_channel_type_combobox), 1);
    g_object_set(mass_channel_type_combobox, "margin-left", 5, NULL);
    g_object_set(mass_channel_type_combobox, "margin-right", 5, NULL);
    gtk_container_add(GTK_CONTAINER(box), mass_channel_type_combobox);

    mass_channel_enable_switch = gtk_switch_new();
    gtk_switch_set_state(mass_channel_enable_switch, false);
    g_object_set(mass_channel_enable_switch, "margin-right", 10, NULL);
    gtk_container_add(GTK_CONTAINER(box), mass_channel_enable_switch);

    button_start = gtk_button_new_with_label("START");
    gtk_container_add(GTK_CONTAINER(box), button_start);
    g_signal_connect(button_start, "clicked", G_CALLBACK(start_button_pressed), mass_channel_enable_switch);
    // g_signal_connect_swapped(button_start, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    // gtk_widget_set_halign(button_start, GTK_ALIGN_END);
    // gtk_widget_set_valign(button_start, GTK_ALIGN_END);
    gtk_widget_set_name(button_start, "button_start");
    g_object_set(button_start, "margin-right", 10, NULL);

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