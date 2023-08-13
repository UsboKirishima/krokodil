#include <kk_main.h>
#include <kk_ui.h>
#include <kk_client.h>
#include <kk_dashboard.h>

#include "../config/token.h"

typedef struct config
{
    char *version;
    char *token;
    char *guild_id;
} t_configs;

t_configs configs = {VERSION, DISCORD_TOKEN, GUILD_ID};

void *client_init(char *token);
char *startUI();

int main(int argc,
         char **argv)
{
    char line[256];
    FILE *token;
    char *_token;

    token = popen("chmod +x scripts/token.sh && sh scripts/token.sh", "r");

    if (token == NULL)
    {
        perror("Pipe returned a error");
    }
    else
    {
        printf("Exit code: %i\n", WEXITSTATUS(pclose(token)));
    }
    pthread_t threads[2];


    //pthread_create(&threads[0], NULL, client_init, DS_TOKEN);
    //pthread_create(&threads[1], NULL, startDashboard, NULL);

    //pthread_join(threads[0], NULL);
    //pthread_join(threads[1], NULL);

    startDashboard();
    client_init(DS_TOKEN);
}