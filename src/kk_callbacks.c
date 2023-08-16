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

    if(mass_c_type == "Text") {
        s_attack.mass_channel_type = 0;
    } else if(mass_c_type == "Voice") {
        s_attack.mass_channel_type = 2;
    }
}