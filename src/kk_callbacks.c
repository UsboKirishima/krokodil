#include <kk_dashboard.h>
#include <kk_css.h>
#include <kk_client.h>
#include <stdbool.h>
#include <kk_callbacks.h>

#include "../config/token.h"

struct attack s_attack;

struct attack s_attack = {
    false, // mass_channel_enabled
    "channel-name", // mass_channel_name
    2,    // mass_channel_count
    true,  // mass_channel_type
    false, // guild_name_enabled
    "Nuked by Krokodil" // guild_name
};
/**
 * Callbacks
 */

/**
 * Module 1 (Callbacks)
 * Mass Channel
 */

void mass_channel_enable_switched(GtkSwitch *widget,
                                  gboolean state,
                                  gpointer user_data)
{
    if (state == TRUE)
    {
        s_attack.mass_channel_enabled = true;
    }
    else
    {
        s_attack.mass_channel_enabled = false;
    }
}

void mass_channel_entry_active(GtkWidget *widget, gpointer data)
{
    s_attack.mass_channel_name = gtk_entry_get_text(GTK_ENTRY(widget));
}

void mass_channel_count_change(GtkWidget *self,
                               GtkScrollType *scroll,
                               gpointer user_data)
{
    s_attack.mass_channel_count = (int)gtk_spin_button_get_value_as_int(self);
}

void guild_name_enable_switched(GtkSwitch *widget,
                                gboolean state,
                                gpointer user_data)
{
    if (state == TRUE)
    {
        s_attack.guild_name_enabled = true;
    }
    else
    {
        s_attack.guild_name_enabled = false;
    }
}
void guild_name_entry_active(GtkWidget *widget, gpointer data)
{
    s_attack.guild_name = (char *)gtk_entry_get_text(GTK_ENTRY(widget));
}

void *client_init(char *TOKEN);

void start_button_pressed(GtkWidget *widget, gpointer data)
{
}