#ifndef KROKODIL_UI_H
#define KROKODIL_UI_H

#include <string.h>
#include <orca/discord.h>
#include <inttypes.h>

void on_ready(struct discord *client);
void mass_channel(struct discord *client, u64_snowflake_t guild_id,
                  char channel_name[15], int count);
void on_message(struct discord *client,
                const struct discord_message *msg);
void *client_init(char *TOKEN);
#endif