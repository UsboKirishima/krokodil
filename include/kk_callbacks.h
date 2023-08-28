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
    char mass_channel_name[15];
    int mass_channel_count;
    int mass_channel_type;

    bool guild_name_enabled;
    char guild_name[15];

    bool dm_all_enabled;
    char dm_message[2000];

    bool channel_delete_all;

    bool rename_channel_enabled;
    char rename_channel_name[30];

    bool presence_enabled;
    char presence_name[30];
    int presence_type;
    char presence_status[20];

    bool nickname_enabled;
    char nickname_name[30];

    bool send_message_enabled;
    char send_message_message[2000];
    int send_message_amount;
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