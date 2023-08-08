#ifndef KROKODIL_DASHBOARD_H
#define KROKODIL_DASHBOARD_H

#include <gtk/gtk.h>
#include <string.h>

void start_button_pressed(GtkWidget *widget,
                          gpointer data);

void activateDashboard(GtkApplication *app,
                       gpointer user_data);

void *startDashboard();

#endif