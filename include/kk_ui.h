#ifndef KROKODIL_UI_H
#define KROKODIL_UI_H

#include <gtk/gtk.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>

void
login_button_pressed(GtkWidget *widget, 
                gpointer data);

void
activate(GtkApplication *app, 
                gpointer user_data);

char 
*startUI();

#endif