#include <kk_main.h>
#include <kk_ui.h>
#include <kk_client.h>
#include <kk_dashboard.h>

typedef struct config
{
    char *version;
    char *token;
    char *guild_id;
} t_configs;

t_configs configs = {VERSION, DISCORD_TOKEN, GUILD_ID};

void *client_init();
int startUI();

int main(int argc,
         char **argv)
{
    pthread_t thread[2];
    // starting the thread
    pthread_create(&thread[0], NULL, client_init, NULL);
    // pthread_create(&thread[1],NULL,startUI,NULL);
    // waiting for completion
    // pthread_join(thread[0], NULL);
    // pthread_join(thread[1],NULL);


    

    if (startUI() == 0)
    {
        startDashboard();
    }
    else
    {
        printf("gogo");
    }

}