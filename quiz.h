#ifndef QUIZ_H
#define QUIZ_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>

#define BACK_LOG 5
#define MAXPLAYER 10

typedef enum    e_mode
{
    UNIQUE,
    MULT
}               t_mode;

typedef struct s_user
{
    char nom[30];
    t_mode mode;
    int score;
}               t_user;

typedef struct  s_participant
{
    char                    id_client[30];
    t_user                  *user;
    int                     fdClient;
    struct s_participant    *next;
}               t_participant;

// t_participant *g_participants_mult = NULL;

char    **get_qst(void);
char    **get_ans(void);
int     tab_len(char **tab);
int     random_int(int min, int max);
void    addback(t_participant **alst, t_participant *new);
int     par_size(t_participant *par);
void    affiche_lst_par(t_participant *parts);
void    affiche_par(t_participant *par);

t_participant	*ft_lstnew(t_user *user, int fdClent);
void            free_pars(t_participant *parts);

#endif

////./client name mode[U M]