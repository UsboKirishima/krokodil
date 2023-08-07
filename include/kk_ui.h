#ifndef KROKODIL_UI_H
#define KROKODIL_UI_H

#include <gtk/gtk.h>
#include <string.h>

void
print_hello(GtkWidget *widget, 
                gpointer data);

void
activate(GtkApplication *app, 
                gpointer user_data);

void
*startUI();

#endif