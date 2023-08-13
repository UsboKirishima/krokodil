#ifndef KROKODIL_DASHBOARD_H
#define KROKODIL_DASHBOARD_H

#include <gtk/gtk.h>
#include <string.h>
#include <stdbool.h>

struct attack
{
    bool mass_channel_enabled;
    char *mass_channel_name;
    int mass_channel_count;
    bool mass_channel_type; // true: text :: false: voice

    bool guild_name_enabled;
    char guild_name[20];
};

extern struct attack s_attack;

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