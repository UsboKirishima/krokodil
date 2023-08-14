#ifndef KROKODIL_DASHBOARD_H
#define KROKODIL_DASHBOARD_H

#include <gtk/gtk.h>
#include <string.h>
#include <stdbool.h>



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