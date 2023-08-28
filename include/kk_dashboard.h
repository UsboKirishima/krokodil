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

    //Stacks
    GtkWidget *stack1; //channels stack
    GtkWidget *users_stack; 
    GtkWidget *roles_stack; 
    GtkWidget *server_stack; 

    //Boxes
    GtkWidget *channels_box;
    GtkWidget *users_box;
    GtkWidget *roles_box;
    GtkWidget *server_box;
    GtkWidget *settings_box;

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

    // Guild icon
    GtkWidget *guild_icon_box;
    GtkWidget *guild_icon_enable_switch;
    GtkWidget *guild_icon_label;
    GtkWidget *guild_icon_file_choser;
    GtkWidget *guild_icon_filter;

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

    //Rename all channels
    GtkWidget *rename_channel_box;
    GtkWidget *rename_channel_enable_switch;
    GtkWidget *rename_channel_label;
    GtkWidget *rename_channel_entry;

    //Presence
    GtkWidget *presence_box;
    GtkWidget *presence_enable_switch;
    GtkWidget *presence_label;
    GtkWidget *presence_entry;
    GtkWidget *presence_type_combobox;
    GtkWidget *presence_status_combobox;

    //Nickname
    GtkWidget *nickname_box;
    GtkWidget *nickname_enable_switch;
    GtkWidget *nickname_label;
    GtkWidget *nickname_entry;

    //Send messages
    GtkWidget *send_message_box;
    GtkWidget *send_message_enable_switch;
    GtkWidget *send_message_label;
    GtkWidget *send_message_name_entry;
    GtkWidget *send_message_count_spin;
    GtkAdjustment *adj2;
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