#include "quiz.h"

char **tab_qst = NULL;
char **tab_ans = NULL;
t_participant *g_participants_mult = NULL;
int health_var = 0;

int random_int(int min, int max)
{
   return min + rand() % (max + 1 - min);
}
void red () {
  printf("\033[1;31m");
}
void green () {
  printf("\033[1;32m");
}
void yellow() {
  printf("\033[1;33m");
}
void reset () {
  printf("\033[0m");
}

void handle_Unique(t_participant *par) {
    char res1[5];
    for (int i = 0; i < 5; i++) {
        int index = random_int(0, tab_len(tab_qst) - 1);//2 
        send(par->fdClient, tab_qst[index], strlen(tab_qst[index]), 0);
        recv(par->fdClient, res1, 5, 0);
        if (strncmp(tab_ans[index], res1, 1) == 0)
        {
            green();
            printf("<<%s>> answer :%s -> correct\n", par->id_client, res1);
            reset();
            par->user->score++;
        }
        else {
            red();
            printf("<<%s>> answer :%s -> false\n", par->id_client, res1);
            reset();
        }
        memset(res1, 0, 5);
    }
    send(par->fdClient, "exit", strlen("exit"), 0);
    int gg = 0;
    if (par->user->score >= 3)
        gg = 1;
    printf("user <<%s>> your finale score is [%d]:", par->id_client, par->user->score);
    if (gg == 1){
        green();
        printf(" tu as gagner\n");
        reset();
    }
    else{
        red();
        printf(" tu as perdu\n");
        reset();
    }
    close(par->fdClient);//cloe connection with client
}

void close_connet_par()//not used
{
    t_participant *tmp;

    tmp = g_participants_mult;
    printf("size=%d\n", par_size(g_participants_mult));
    if (!tmp)
        printf("tmp vide\n");
    while (tmp)
    {
        printf("==============im own to close %s:%d\n", tmp->id_client,tmp->fdClient);
        close(tmp->fdClient);
        tmp = tmp->next;
    }
}

void *health(void *arg)
{
    t_participant *par = (t_participant *)arg;
    while (1) {
        if (health_var == 1)
            break ;
    }
    close(par->fdClient);
    // close_connet_par();
    return NULL;
}
 
void handle_group(t_participant *par)
{
    char res1[5];
    pthread_t healt_thr;
    affiche_lst_par(g_participants_mult);////
    pthread_create(&healt_thr, NULL, health, (void *)par);
    while (1)
    {
        int index = random_int(0, tab_len(tab_qst) - 1);
        if (health_var == 1)
            break ;
        else
        {
            send(par->fdClient, tab_qst[index], strlen(tab_qst[index]), 0);
            recv(par->fdClient, res1, 5, 0);
            if (health_var == 1)
                break ;
            // printf("%s\n", res1);
            if (strncmp(tab_ans[index], res1, 1) == 0)
            {
                green();
                printf("<<%s>> answer :%s -> correct\n", par->id_client, res1);
                reset();
                par->user->score++;
            }
            else {
                red();
                printf("<<%s>> answer :%s -> false\n", par->id_client, res1);
                reset();
            }
            if (par->user->score >= 3)
            {
                yellow();
                printf("WINNER <<%s>>\n", par->id_client);
                reset();
                health_var = 1;
                // free_pars(g_participants_mult);////////
                break ;
            }
            memset(res1, 0, 5);
        }
    }
    pthread_join(healt_thr, NULL);
    health_var = 0;
    g_participants_mult = NULL;///free list 
    sleep(1);
}

void *function(void *arg) {
    int socket = *(int *)arg;
    t_user user;
    /////par
    recv(socket, &user, sizeof(user), 0);
    ///init par
    t_participant *par = ft_lstnew(&user, socket);
    ////////////
    if (user.mode == UNIQUE) {
        printf("user <<%s>> want to play on UNIQUE MODE\n", user.nom);
        handle_Unique(par);
    }
    else if (user.mode == MULT) {
        printf("user <<%s>> want to play on MULTIPLE MODE\n", user.nom);
        addback(&g_participants_mult, par);
        handle_group(par);
    }
    close(socket);
    return NULL;
}

int main() {
    int socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServer == -1)
    {
        printf("error create server socket \n");
        return 1;
    }
    struct sockaddr_in addrServer;
    addrServer.sin_family = AF_INET;
    addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrServer.sin_port = htons(30000);
    // printf("address of server %s\n", (addrServer.sin_addr.s_addr));
    while (bind(socketServer, (struct sockaddr *)&addrServer, sizeof(addrServer)) == -1)
    {
        printf("error in bind reser\n");
    }
    printf("bind : %d\n", socketServer);
    if (listen(socketServer, BACK_LOG) == -1)
    {
        printf("error in lisen\n");
        return 1;
    }
    printf("listen\n");

    //////////////////////////////////////////////
    tab_qst = get_qst();
    tab_ans = get_ans();
    /////////////////////////////////////////////
    pthread_t clientThread[MAXPLAYER];
    int socketClient;
    int num = 0;
    while (num != MAXPLAYER)
    {
        struct sockaddr_in addrClient;
        socklen_t csize = sizeof(addrClient);
        socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);
        if (socketClient == -1)
        {
            printf("error in creating clien handle socket\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("accept client %d\n", socketClient);
            int *arg = malloc(sizeof(int));
            *arg = socketClient;
            pthread_create(&clientThread[num], NULL, function, arg);
            num++;
        }
    }
    //one now
    close(socketServer);
    printf("close\n");
    return 0;
}