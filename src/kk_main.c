#include <kk_main.h>
#include <kk_ui.h>
#include <kk_client.h>

typedef struct config
{
  char *version;
  char *token;
  char *guild_id;
} t_configs; 

t_configs configs = {VERSION, DISCORD_TOKEN, GUILD_ID}; 


int main(int argc,
         char **argv)
{
    int status = startUI(argc, argv);

    client_init(configs.token, configs.guild_id);

    return status;
}
