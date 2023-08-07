#ifndef KROKODIL_UI_H
#define KROKODIL_UI_H

#include <string.h>
#include <orca/discord.h>

void on_ready(struct discord *client);

void on_message(struct discord *client,
                const struct discord_message *msg);

void *client_init();
#endif