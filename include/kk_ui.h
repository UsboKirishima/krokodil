#ifndef KROKODIL_UI_H
#define KROKODIL_UI_H

#include <gtk/gtk.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>

struct config
{
    char version[200];
    char token[200];
    char guild_id[200];
};

extern struct config t_configs;


void
login_button_pressed(GtkWidget *widget, 
                gpointer data);

void
activate(GtkApplication *app, 
                gpointer user_data);

char 
*startUI();

#endif