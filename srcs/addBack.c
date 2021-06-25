#include "../quiz.h"

void affiche_par(t_participant *par)
{
	printf("nom : <<%s>> score <<%d>> \n", par->id_client, par->user->score);
}

void affiche_lst_par(t_participant *parts)
{
	t_participant *tmp;

	tmp = parts;
	while (tmp)
	{
		affiche_par(tmp);
		tmp = tmp->next;
	}
}

void free_pars(t_participant *parts)
{
	t_participant *tmp;
	// t_participant *prev;

	// tmp = parts;
	// prev = parts;
	while (parts != NULL)
	{
		tmp = parts;
		parts = parts->next;
		free(tmp);
	}
}

t_participant	*ft_lstnew(t_user *user, int fdClent)
{
	t_participant	*new;

	new = (t_participant *)malloc(sizeof(t_participant));
	if (!new)
		return (NULL);
	strncpy(new->id_client, user->nom, strlen(user->nom));
	new->fdClient = fdClent;
	new->user = user;
	new->next = NULL;
	return (new);
}

int par_size(t_participant *par)
{
	t_participant *tmp;
	int i = 0;

	tmp = par;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return i;
}

void addback(t_participant **alst, t_participant *new)
{
    t_participant	*tmp;

	if (!alst || !new)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	tmp = (*alst);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

// t_participant *g_participants_mult = NULL;


// int main() {
// 	t_user user1;
// 	t_user user2;
// 	// t_participant *p1 = NULL;
// 	// t_participant *p2 = NULL;

// 	strncpy(user1.nom, "yasser", 30);
// 	user1.score = 10;
// 	user1.mode = MULT;
// 	////
// 	strncpy(user2.nom, "moha", 30);
// 	user2.score = 20;
// 	user2.mode = MULT;
// 	/////
// 	// p1 = malloc(sizeof(t_participant));
// 	// p2 = malloc(sizeof(t_participant));
// 	/////
// 	// p1->fdClient = 0;
// 	// strncpy(p1->id_client, user1.nom, 30);
// 	// p1->user = &user1;
// 	// p1->next = NULL;
// 	////
// 	// p2->fdClient = 0;
// 	// strncpy(p2->id_client, user2.nom, 30);
// 	// p2->user = &user2;
// 	// p2->next = NULL;

// 	addback(&g_participants_mult, ft_lstnew(&user1, 4));
// 	addback(&g_participants_mult, ft_lstnew(&user2, 5));
// 	addback(&g_participants_mult, ft_lstnew(&user2, 5));
// 	printf("size = %d\n", par_size(g_participants_mult));
// 	// affiche_par(p1->next);
// 	// addback(&g_participants_mult, p1);
// 	// addback(&g_participants_mult, p2);
	
// 	affiche_lst_par(g_participants_mult);


// 	return 0;
// }