#ifndef KROKODIL_DASHBOARD_H
#define KROKODIL_DASHBOARD_H

#include <gtk/gtk.h>
#include <string.h>
#include <stdbool.h>

struct dashboardWidgets
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *logs_box;
    GtkWidget *button_start;
    GtkWidget *button_start_box;
    GtkWidget *button_stop;
    GtkWidget *button_logs;
    GtkWidget *sidebar;
    GtkWidget *stack1;

    // Mass channel widgets
    GtkWidget *mass_channel_box;
    GtkWidget *mass_channel_enable_switch;
    GtkWidget *mass_channel_label;
    GtkWidget *mass_channel_name_entry;
    GtkWidget *mass_channel_count_spin;
    GtkWidget *mass_channel_type_combobox;

    // Guild name widgets
    GtkWidget *guild_name_box;
    GtkWidget *guild_name_enable_switch;
    GtkWidget *guild_name_label;
    GtkWidget *guild_name_entry;

    // Dm all
    GtkWidget *dm_all_box;
    GtkWidget *dm_all_enable_switch;
    GtkWidget *dm_all_label;
    GtkWidget *dm_all_entry;

    // Delete all channels
    GtkWidget *channel_delete_box;
    GtkWidget *channel_delete_enable_switch;
    GtkWidget *channel_delete_label;
    GtkAdjustment *adj;
};


void mass_channel_enable_switched(GtkSwitch *widget,
                                  gboolean state,
                                  gpointer user_data);

void mass_channel_entry_active(GtkWidget *widget,
                               gpointer data);

void start_button_pressed(GtkWidget *widget,
                          gpointer data);

void activateDashboard(GtkApplication *app,
                       gpointer user_data);

void *startDashboard();

#endif