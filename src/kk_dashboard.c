#include <kk_dashboard.h>
#include <kk_css.h>
#include <kk_client.h>
#include <stdbool.h>
#include <kk_callbacks.h>

#include "../config/token.h"

struct dashboardWidgets widgets;

void activateDashboard(GtkApplication *app,
                       gpointer user_data)
{

    gtk_css();

    widgets.window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(widgets.window), "Krokodil");
    gtk_window_set_default_size(GTK_WINDOW(widgets.window), 900, 500);
    gtk_window_set_resizable(GTK_WINDOW(widgets.window), FALSE);

    GtkWidget *fixed = gtk_fixed_new();
    gtk_widget_set_name(fixed, "fixed");
    gtk_container_add(GTK_CONTAINER(widgets.window), fixed);

    // Sidebar
    widgets.sidebar = gtk_stack_sidebar_new();
    gtk_widget_set_name(widgets.sidebar, "sidebar");
    gtk_fixed_put(GTK_FIXED(fixed), widgets.sidebar, 0, 0);
    gtk_widget_set_size_request(widgets.sidebar, 150, 550);

    // Stack
    widgets.stack1 = gtk_stack_new();
    gtk_widget_set_name(widgets.stack1, "stack1");
    gtk_widget_set_size_request(widgets.stack1, 550, 500);
    gtk_fixed_put(GTK_FIXED(fixed), widgets.stack1, 150, 0);
    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(widgets.sidebar), GTK_STACK(widgets.stack1));

    // Switcher
    GtkWidget *switcher = gtk_stack_switcher_new();
    gtk_widget_set_name(switcher, "switcher");
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(switcher), GTK_STACK(widgets.stack1));

    widgets.box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(widgets.box, GTK_ALIGN_START);
    gtk_widget_set_valign(widgets.box, GTK_ALIGN_START);
    gtk_stack_add_titled(GTK_STACK(widgets.stack1), GTK_WIDGET(widgets.box), "channels", "Channels");

    widgets.users_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(widgets.users_box, GTK_ALIGN_START);
    gtk_widget_set_valign(widgets.users_box, GTK_ALIGN_START);
    gtk_stack_add_titled(GTK_STACK(widgets.stack1), GTK_WIDGET(widgets.users_box), "users", "Users");

    widgets.roles_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(widgets.roles_box, GTK_ALIGN_START);
    gtk_widget_set_valign(widgets.roles_box, GTK_ALIGN_START);
    gtk_stack_add_titled(GTK_STACK(widgets.stack1), GTK_WIDGET(widgets.roles_box), "roles", "Roles");

    widgets.server_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(widgets.server_box, GTK_ALIGN_START);
    gtk_widget_set_valign(widgets.server_box, GTK_ALIGN_START);
    gtk_stack_add_titled(GTK_STACK(widgets.stack1), GTK_WIDGET(widgets.server_box), "server", "Server");

    widgets.settings_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(widgets.settings_box, GTK_ALIGN_START);
    gtk_widget_set_valign(widgets.settings_box, GTK_ALIGN_START);
    gtk_stack_add_titled(GTK_STACK(widgets.stack1), GTK_WIDGET(widgets.settings_box), "settings", "Settings");

    /**
     * CHANNELS
     */

    /**
     * Channels delete
     */

    widgets.channel_delete_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(widgets.box), widgets.channel_delete_box, TRUE, TRUE, 0);
    gtk_widget_set_name(widgets.channel_delete_box, "channel_delete_box");
    g_object_set(widgets.channel_delete_box, "margin-top", 10, NULL);
    g_object_set(widgets.channel_delete_box, "margin-left", 10, NULL);
    gtk_widget_set_halign(widgets.channel_delete_box, GTK_ALIGN_START);
    gtk_widget_set_valign(widgets.channel_delete_box, GTK_ALIGN_START);

    widgets.channel_delete_enable_switch = gtk_switch_new();
    gtk_switch_set_state(widgets.channel_delete_enable_switch, false);
    gtk_container_add(GTK_CONTAINER(widgets.channel_delete_box), widgets.channel_delete_enable_switch);
    g_object_set(widgets.channel_delete_enable_switch, "margin-left", 10, NULL);
    g_object_set(widgets.channel_delete_enable_switch, "margin-right", 10, NULL);

    widgets.channel_delete_label = gtk_label_new("DELETE ALL");
    gtk_container_add(GTK_CONTAINER(widgets.channel_delete_box), widgets.channel_delete_label);
    gtk_widget_set_name(widgets.channel_delete_label, "channel_delete_label");
    gtk_widget_set_halign(widgets.channel_delete_label, GTK_ALIGN_CENTER);
    gtk_widget_set_name(widgets.channel_delete_label, "channel_delete_label");
    g_object_set(widgets.channel_delete_label, "margin-left", 20, NULL);
    g_object_set(widgets.channel_delete_label, "margin-right", 20, NULL);

    /**
     * Mass Channel
     */

    widgets.mass_channel_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(widgets.box), widgets.mass_channel_box, TRUE, TRUE, 0);
    gtk_widget_set_name(widgets.mass_channel_box, "mass_channel_box");
    g_object_set(widgets.mass_channel_box, "margin-top", 10, NULL);
    g_object_set(widgets.mass_channel_box, "margin-left", 10, NULL);
    gtk_widget_set_halign(widgets.mass_channel_box, GTK_ALIGN_START);
    gtk_widget_set_valign(widgets.mass_channel_box, GTK_ALIGN_START);

    widgets.mass_channel_enable_switch = gtk_switch_new();
    gtk_switch_set_state(widgets.mass_channel_enable_switch, false);
    gtk_container_add(GTK_CONTAINER(widgets.mass_channel_box), widgets.mass_channel_enable_switch);
    g_object_set(widgets.mass_channel_enable_switch, "margin-left", 10, NULL);
    g_object_set(widgets.mass_channel_enable_switch, "margin-right", 10, NULL);

    widgets.mass_channel_label = gtk_label_new("MASS CREATE");
    gtk_container_add(GTK_CONTAINER(widgets.mass_channel_box), widgets.mass_channel_label);
    gtk_widget_set_halign(widgets.mass_channel_label, GTK_ALIGN_CENTER);
    gtk_widget_set_name(widgets.mass_channel_label, "mass_channel_label");
    g_object_set(widgets.mass_channel_label, "margin-left", 10, NULL);
    g_object_set(widgets.mass_channel_label, "margin-right", 10, NULL);

    widgets.mass_channel_name_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(widgets.mass_channel_name_entry), 15);
    gtk_container_add(GTK_CONTAINER(widgets.mass_channel_box), widgets.mass_channel_name_entry);
    g_object_set(widgets.mass_channel_name_entry, "margin-left", 10, NULL);
    g_object_set(widgets.mass_channel_name_entry, "margin-right", 10, NULL);
    gtk_entry_set_text(widgets.mass_channel_name_entry, "channel-name");

    widgets.adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 1.0, 200.0, 1.0,
                                                      5.0, 0.0);
    widgets.mass_channel_count_spin = gtk_spin_button_new(widgets.adj, 0, 0);
    gtk_container_add(GTK_CONTAINER(widgets.mass_channel_box), widgets.mass_channel_count_spin);
    g_object_set(widgets.mass_channel_count_spin, "margin-left", 10, NULL);
    g_object_set(widgets.mass_channel_count_spin, "margin-right", 10, NULL);

    widgets.mass_channel_type_combobox = gtk_combo_box_text_new();
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets.mass_channel_type_combobox), NULL, "Text");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets.mass_channel_type_combobox), NULL, "Voice");
    gtk_combo_box_set_active(GTK_COMBO_BOX(widgets.mass_channel_type_combobox), 0);
    g_object_set(widgets.mass_channel_type_combobox, "margin-left", 10, NULL);
    g_object_set(widgets.mass_channel_type_combobox, "margin-right", 10, NULL);
    gtk_container_add(GTK_CONTAINER(widgets.mass_channel_box), widgets.mass_channel_type_combobox);

    /**
     * Rename all channels
     */
    widgets.rename_channel_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(widgets.box), widgets.rename_channel_box, TRUE, TRUE, 0);
    gtk_widget_set_name(widgets.rename_channel_box, "dm_all_box");
    g_object_set(widgets.rename_channel_box, "margin-top", 10, NULL);
    g_object_set(widgets.rename_channel_box, "margin-left", 10, NULL);
    gtk_widget_set_halign(widgets.rename_channel_box, GTK_ALIGN_START);
    gtk_widget_set_valign(widgets.rename_channel_box, GTK_ALIGN_START);

    widgets.rename_channel_enable_switch = gtk_switch_new();
    gtk_switch_set_state(widgets.rename_channel_enable_switch, false);
    gtk_container_add(GTK_CONTAINER(widgets.rename_channel_box), widgets.rename_channel_enable_switch);
    g_object_set(widgets.rename_channel_enable_switch, "margin-left", 10, NULL);
    g_object_set(widgets.rename_channel_enable_switch, "margin-right", 10, NULL);

    widgets.rename_channel_label = gtk_label_new("RENAME ALL");
    gtk_container_add(GTK_CONTAINER(widgets.rename_channel_box), widgets.rename_channel_label);
    gtk_widget_set_name(widgets.rename_channel_label, "rename_channel_label");
    gtk_widget_set_halign(widgets.rename_channel_label, GTK_ALIGN_CENTER);
    g_object_set(widgets.rename_channel_label, "margin-left", 15, NULL);
    g_object_set(widgets.rename_channel_label, "margin-right", 15, NULL);

    widgets.rename_channel_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(widgets.rename_channel_entry), 2000);
    gtk_container_add(GTK_CONTAINER(widgets.rename_channel_box), widgets.rename_channel_entry);
    g_object_set(widgets.rename_channel_entry, "margin-left", 10, NULL);
    g_object_set(widgets.rename_channel_entry, "margin-right", 10, NULL);
    gtk_entry_set_text(widgets.rename_channel_entry, "nuked-by-krokodil");

    /**
     * SERVER
     */

    /**
     * Guild Name
     */

    widgets.guild_name_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(widgets.server_box), widgets.guild_name_box, TRUE, TRUE, 0);
    gtk_widget_set_name(widgets.guild_name_box, "guild_name_box");
    g_object_set(widgets.guild_name_box, "margin-top", 10, NULL);
    g_object_set(widgets.guild_name_box, "margin-left", 10, NULL);
    gtk_widget_set_halign(widgets.guild_name_box, GTK_ALIGN_START);
    gtk_widget_set_valign(widgets.guild_name_box, GTK_ALIGN_START);

    widgets.guild_name_enable_switch = gtk_switch_new();
    gtk_switch_set_state(widgets.guild_name_enable_switch, false);
    gtk_container_add(GTK_CONTAINER(widgets.guild_name_box), widgets.guild_name_enable_switch);
    g_object_set(widgets.guild_name_enable_switch, "margin-left", 10, NULL);
    g_object_set(widgets.guild_name_enable_switch, "margin-right", 10, NULL);

    widgets.guild_name_label = gtk_label_new("GUILD NAME");
    gtk_container_add(GTK_CONTAINER(widgets.guild_name_box), widgets.guild_name_label);
    gtk_widget_set_name(widgets.guild_name_label, "guild_name_label");
    gtk_widget_set_halign(widgets.guild_name_label, GTK_ALIGN_CENTER);
    gtk_widget_set_name(widgets.guild_name_label, "guild_name_label");
    g_object_set(widgets.guild_name_label, "margin-left", 20, NULL);
    g_object_set(widgets.guild_name_label, "margin-right", 20, NULL);

    widgets.guild_name_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(widgets.guild_name_entry), 20);
    gtk_container_add(GTK_CONTAINER(widgets.guild_name_box), widgets.guild_name_entry);
    g_object_set(widgets.guild_name_entry, "margin-left", 10, NULL);
    g_object_set(widgets.guild_name_entry, "margin-right", 10, NULL);
    gtk_entry_set_text(widgets.guild_name_entry, "Nuked by Krokodil");

    /**
     * USERS
     */

    /**
     * Dm All
     */

    widgets.dm_all_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(widgets.users_box), widgets.dm_all_box, TRUE, TRUE, 0);
    gtk_widget_set_name(widgets.dm_all_box, "dm_all_box");
    g_object_set(widgets.dm_all_box, "margin-top", 10, NULL);
    g_object_set(widgets.dm_all_box, "margin-left", 10, NULL);
    gtk_widget_set_halign(widgets.dm_all_box, GTK_ALIGN_START);
    gtk_widget_set_valign(widgets.dm_all_box, GTK_ALIGN_START);

    widgets.dm_all_enable_switch = gtk_switch_new();
    gtk_switch_set_state(widgets.dm_all_enable_switch, false);
    gtk_container_add(GTK_CONTAINER(widgets.dm_all_box), widgets.dm_all_enable_switch);
    g_object_set(widgets.dm_all_enable_switch, "margin-left", 10, NULL);
    g_object_set(widgets.dm_all_enable_switch, "margin-right", 10, NULL);

    widgets.dm_all_label = gtk_label_new("DM ALL");
    gtk_container_add(GTK_CONTAINER(widgets.dm_all_box), widgets.dm_all_label);
    gtk_widget_set_name(widgets.dm_all_label, "dm_all_label");
    gtk_widget_set_halign(widgets.dm_all_label, GTK_ALIGN_CENTER);
    gtk_widget_set_name(widgets.dm_all_label, "dm_all_label");
    g_object_set(widgets.dm_all_label, "margin-left", 35, NULL);
    g_object_set(widgets.dm_all_label, "margin-right", 40, NULL);

    widgets.dm_all_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(widgets.dm_all_entry), 2000);
    gtk_container_add(GTK_CONTAINER(widgets.dm_all_box), widgets.dm_all_entry);
    g_object_set(widgets.dm_all_entry, "margin-left", 10, NULL);
    g_object_set(widgets.dm_all_entry, "margin-right", 10, NULL);
    gtk_entry_set_text(widgets.dm_all_entry, "Server got nuked!!!");

    /**
     * SETTINGS
     */

    widgets.presence_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(widgets.settings_box), widgets.presence_box, TRUE, TRUE, 0);
    gtk_widget_set_name(widgets.presence_box, "dm_all_box");
    g_object_set(widgets.presence_box, "margin-top", 10, NULL);
    g_object_set(widgets.presence_box, "margin-left", 10, NULL);
    gtk_widget_set_halign(widgets.presence_box, GTK_ALIGN_START);
    gtk_widget_set_valign(widgets.presence_box, GTK_ALIGN_START);

    widgets.presence_enable_switch = gtk_switch_new();
    gtk_switch_set_state(widgets.presence_enable_switch, false);
    gtk_container_add(GTK_CONTAINER(widgets.presence_box), widgets.presence_enable_switch);
    g_object_set(widgets.presence_enable_switch, "margin-left", 10, NULL);
    g_object_set(widgets.presence_enable_switch, "margin-right", 10, NULL);

    widgets.presence_label = gtk_label_new("PRESENCE");
    gtk_container_add(GTK_CONTAINER(widgets.presence_box), widgets.presence_label);
    gtk_widget_set_name(widgets.presence_label, "presence_label");
    gtk_widget_set_halign(widgets.presence_label, GTK_ALIGN_CENTER);
    g_object_set(widgets.presence_label, "margin-left", 20, NULL);
    g_object_set(widgets.presence_label, "margin-right", 20, NULL);

    widgets.presence_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(widgets.presence_entry), 30);
    gtk_container_add(GTK_CONTAINER(widgets.presence_box), widgets.presence_entry);
    g_object_set(widgets.presence_entry, "margin-left", 10, NULL);
    g_object_set(widgets.presence_entry, "margin-right", 10, NULL);
    gtk_entry_set_text(widgets.presence_entry, "#KrokodilOnTop");

    widgets.presence_type_combobox = gtk_combo_box_text_new();
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets.presence_type_combobox), NULL, "Playing");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets.presence_type_combobox), NULL, "Watching");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets.presence_type_combobox), NULL, "Streaming");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets.presence_type_combobox), NULL, "Competing");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets.presence_type_combobox), NULL, "Listening");
    gtk_combo_box_set_active(GTK_COMBO_BOX(widgets.presence_type_combobox), 0);
    g_object_set(widgets.presence_type_combobox, "margin-left", 10, NULL);
    g_object_set(widgets.presence_type_combobox, "margin-right", 10, NULL);
    gtk_container_add(GTK_CONTAINER(widgets.presence_box), widgets.presence_type_combobox);

    widgets.presence_status_combobox = gtk_combo_box_text_new();
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets.presence_status_combobox), NULL, "online");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets.presence_status_combobox), NULL, "dnd");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets.presence_status_combobox), NULL, "idle");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgets.presence_status_combobox), NULL, "offline");
    gtk_combo_box_set_active(GTK_COMBO_BOX(widgets.presence_status_combobox), 0);
    g_object_set(widgets.presence_status_combobox, "margin-left", 10, NULL);
    g_object_set(widgets.presence_status_combobox, "margin-right", 10, NULL);
    gtk_container_add(GTK_CONTAINER(widgets.presence_box), widgets.presence_status_combobox);

    //Nickname

    widgets.nickname_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(widgets.settings_box), widgets.nickname_box, TRUE, TRUE, 0);
    gtk_widget_set_name(widgets.nickname_box, "dm_all_box");
    g_object_set(widgets.nickname_box, "margin-top", 10, NULL);
    g_object_set(widgets.nickname_box, "margin-left", 10, NULL);
    gtk_widget_set_halign(widgets.nickname_box, GTK_ALIGN_START);
    gtk_widget_set_valign(widgets.nickname_box, GTK_ALIGN_START);
    
    widgets.nickname_enable_switch = gtk_switch_new();
    gtk_switch_set_state(widgets.nickname_enable_switch, false);
    gtk_container_add(GTK_CONTAINER(widgets.nickname_box), widgets.nickname_enable_switch);
    g_object_set(widgets.nickname_enable_switch, "margin-left", 10, NULL);
    g_object_set(widgets.nickname_enable_switch, "margin-right", 10, NULL);
    
    widgets.nickname_label = gtk_label_new("NICKNAME");
    gtk_container_add(GTK_CONTAINER(widgets.nickname_box), widgets.nickname_label);
    gtk_widget_set_name(widgets.nickname_label, "nickname_label");
    gtk_widget_set_halign(widgets.nickname_label, GTK_ALIGN_CENTER);
    g_object_set(widgets.nickname_label, "margin-left", 20, NULL);
    g_object_set(widgets.nickname_label, "margin-right", 20, NULL);
    
    widgets.nickname_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(widgets.nickname_entry), 30);
    gtk_container_add(GTK_CONTAINER(widgets.nickname_box), widgets.nickname_entry);
    g_object_set(widgets.nickname_entry, "margin-left", 10, NULL);
    g_object_set(widgets.nickname_entry, "margin-right", 10, NULL);
    gtk_entry_set_text(widgets.nickname_entry, "Krokodil");

    /**
     * Start Button
     */

    widgets.button_start = gtk_button_new_with_label("START");
    gtk_container_add(GTK_CONTAINER(widgets.box), widgets.button_start);
    g_signal_connect(widgets.button_start, "clicked", G_CALLBACK(start_button_pressed), &widgets);
    g_signal_connect_swapped(widgets.button_start, "clicked", G_CALLBACK(gtk_widget_destroy), widgets.window);
    gtk_widget_set_valign(widgets.button_start, GTK_ALIGN_END);
    gtk_widget_set_name(widgets.button_start, "button_start");

    gtk_widget_show_all(widgets.window);
}

void *startDashboard()
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.krokodil.dashboard", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activateDashboard), NULL);
    status = g_application_run(G_APPLICATION(app), NULL, NULL);
    g_object_unref(app);
}