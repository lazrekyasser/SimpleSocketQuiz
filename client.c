#include "quiz.h"


int main(int ac , char **av) {
    t_user user;
    char qst[200];
    int socketClient = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrClient;
    addrClient.sin_family = AF_INET;
    addrClient.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrClient.sin_port = htons(30000);

    if(ac < 3)
    {
        printf("error in nbr agrs\n");
        return 1;
    }
    if (connect(socketClient, (const struct sockaddr *)&addrClient, sizeof(addrClient)) == -1)
    {
        printf("client can't connect to server \n");
        return 1;
    }
    printf("connecte\n");

    //////
    strncpy(user.nom, av[1], sizeof(user.nom));
    if (strcmp(av[2], "U") == 0)
        user.mode = UNIQUE;
    else if (strcmp(av[2], "M") == 0)
        user.mode = MULT;
    else
    {
        printf("error in mode of user \n");
        return 1;
    }
    user.score = 0;
    ///////
    send(socketClient, &user, sizeof(user), 0);
    printf("in send my info to server\n");
    printf("-----Begin-------\n");
    char ans[10];
    memset(ans, 0, 10);
    memset(qst, 0, 200);
    while (1)
    {
        int r = recv(socketClient, qst, 200, 0);
        if (r == 0)
        {
            printf("Closed by the server\n");
            printf("-----End-------\n");
            exit(0);
        }
        if (!strcmp(qst, "exit"))
            break; 
        printf("Qst <%s> : \n", qst);
        scanf("%s", ans);
        send(socketClient, ans, 2, 0);
        memset(ans, 0, 10);
        memset(qst, 0, 200);
    }
    printf("-----End-------\n");
    close(socketClient);//close connection with server
    return 0;
}
