#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <kk_css.h>

void gtk_css() {
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen,GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    const gchar *home = "styles/kk_dashboard.css";
    GError *error = 0;
    gtk_css_provider_load_from_file(provider,g_file_new_for_path(home), &error);
    g_object_unref(provider);
}