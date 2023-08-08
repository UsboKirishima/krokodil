#include <kk_client.h>
#include <kk_config.h>

#include <string.h>
#include <orca/discord.h>

void on_ready(struct discord *client)
{
    const struct discord_user *bot = discord_get_self(client);
    log_info("Logged in as %s!", bot->username);
}

void on_message(struct discord *client,
                const struct discord_message *msg)
{
    if (strcmp(msg->content, "ping") != 0)
        return;

    discord_delete_channel(client, msg->channel_id, NULL);
    discord_async_next(client, NULL);
    struct discord_create_message_params params = {.content = "pong"};
    discord_create_message(client, msg->channel_id, &params, NULL);
}

void *client_init()
{
    struct discord *client = discord_init(DISCORD_TOKEN);
    discord_set_on_ready(client, &on_ready);
    discord_set_on_message_create(client, &on_message);
    discord_run(client);
}