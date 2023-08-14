#ifndef KROKODIL_CALLBACKS_H
#define KROKODIL_CALLBACKS_H

#include <string.h>
#include <gtk/gtk.h>
#include <inttypes.h>

#include <kk_dashboard.h>
#include <kk_css.h>
#include <kk_client.h>
#include <stdbool.h>

#include "../config/token.h"

struct attack
{
    bool mass_channel_enabled;
    char *mass_channel_name;
    int mass_channel_count;
    bool mass_channel_type; // true: text :: false: voice

    bool guild_name_enabled;
    char *guild_name;
};

extern struct attack s_attack;
/**
 * Callbacks
 */

/**
 * Module 1 (Callbacks)
 * Mass Channel
 */

void mass_channel_enable_switched(GtkSwitch *widget,
                                  gboolean state,
                                  gpointer user_data);

void mass_channel_entry_active(GtkWidget *widget, gpointer data);

void mass_channel_count_change(GtkWidget *self,
                               GtkScrollType *scroll,
                               gpointer user_data);

void guild_name_enable_switched(GtkSwitch *widget,
                                  gboolean state,
                                  gpointer user_data);

void guild_name_entry_active(GtkWidget *widget, gpointer data);

void start_button_pressed(GtkWidget *widget, gpointer data);

#endif