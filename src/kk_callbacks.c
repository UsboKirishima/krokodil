#include <kk_dashboard.h>
#include <kk_css.h>
#include <kk_client.h>
#include <stdbool.h>
#include <kk_callbacks.h>
#include <string.h>

#include "../config/token.h"

struct attack s_attack;
/*
struct attack s_attack = {
    false,              // mass_channel_enabled
    "channel-name",     // mass_channel_name
    2,                  // mass_channel_count
    true,               // mass_channel_type
    false,              // guild_name_enabled
    "Nuked by Krokodil" // guild_name
};*/

void *client_init(char *TOKEN);

void start_button_pressed(GtkWidget *widget, gpointer data)
{
    struct dashboardWidgets *w = (struct dashboardWidgets *)data;

    /**
     * Mass channel settings
     */

    if (gtk_switch_get_state(w->mass_channel_enable_switch) == TRUE)
    {
        s_attack.mass_channel_enabled = true;
    }
    else
    {
        s_attack.mass_channel_enabled = false;
    }

    char *mass_channel_name = gtk_entry_get_text((GtkEntry *)w->mass_channel_name_entry);
    strcpy(s_attack.mass_channel_name, mass_channel_name);

    s_attack.mass_channel_count = gtk_spin_button_get_value_as_int(w->mass_channel_count_spin);

    char *mass_c_type = gtk_combo_box_text_get_active_text(w->mass_channel_type_combobox);

    if (mass_c_type == "Text")
    {
        s_attack.mass_channel_type = 0;
    }
    else if (mass_c_type == "Voice")
    {
        s_attack.mass_channel_type = 2;
    }

    /**
     * Guild name settings
     */

    if (gtk_switch_get_state(w->guild_name_enable_switch) == TRUE)
    {
        s_attack.guild_name_enabled = true;
    }
    else
    {
        s_attack.guild_name_enabled = false;
    }

    char *_guild_name = gtk_entry_get_text((GtkEntry *)w->guild_name_entry);
    strcpy(s_attack.guild_name, _guild_name);

    /**
     * Dm all settings
     */

    if (gtk_switch_get_state(w->dm_all_enable_switch) == TRUE)
    {
        s_attack.dm_all_enabled = true;
    }
    else
    {
        s_attack.dm_all_enabled = false;
    }

    char *_dm_all_massage = gtk_entry_get_text((GtkEntry *)w->dm_all_entry);
    strcpy(s_attack.dm_message, _dm_all_massage);

    /**
     * Channels delete all
     */

    if (gtk_switch_get_state(w->channel_delete_enable_switch) == TRUE)
    {
        s_attack.channel_delete_all = true;
    }
    else
    {
        s_attack.channel_delete_all = false;
    }

    /**
     * Rename all channels
     */
    if (gtk_switch_get_state(w->rename_channel_enable_switch) == TRUE)
    {
        s_attack.rename_channel_enabled = true;
    }
    else
    {
        s_attack.rename_channel_enabled = false;
    }

    char *rename_c_name = gtk_entry_get_text((GtkEntry *)w->rename_channel_entry);
    strcpy(s_attack.rename_channel_name, rename_c_name);

    /**
     * Presence
     */

    if (gtk_switch_get_state(w->presence_enable_switch) == TRUE)
    {
        s_attack.presence_enabled = true;
    }
    else
    {
        s_attack.presence_enabled = false;
    }

    char *presence_c_name = gtk_entry_get_text((GtkEntry *)w->presence_entry);
    strcpy(s_attack.presence_name, presence_c_name);

    char *presence_c_type = gtk_combo_box_text_get_active_text(w->presence_type_combobox);

    /**
     * Playing   : 0
     * Streaming : 1
     * Listening : 2
     * Watching  : 3
     * Custom    : 4
     * Competing : 5
     */

    if (presence_c_type == "Playing")
    {
        s_attack.presence_type = 0;
    }
    if (presence_c_type == "Watching")
    {
        s_attack.presence_type = 3;
    }
    if (presence_c_type == "Streaming")
    {
        s_attack.presence_type = 1;
    }
    if (presence_c_type == "Competing")
    {
        s_attack.presence_type = 5;
    }
    if (presence_c_type == "Listening")
    {
        s_attack.presence_type = 2;
    }

    /**
     * 'online', 'dnd', 'idle', 'offline'
     */
    char *presence_c_status = gtk_combo_box_text_get_active_text(w->presence_status_combobox);
    strcpy(s_attack.presence_status, presence_c_status);

    /**
     * NICKNAME
     */

    if (gtk_switch_get_state(w->nickname_enable_switch) == TRUE)
    {
        s_attack.nickname_enabled = true;
    }
    else
    {
        s_attack.nickname_enabled = false;
    }

    char *nickname_c_name = gtk_entry_get_text((GtkEntry *)w->nickname_entry);
    strcpy(s_attack.nickname_name, nickname_c_name);
}