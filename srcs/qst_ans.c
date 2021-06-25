#include "../quiz.h"
#include "get_next_line.h"

int tab_len(char **tab) {
    int i = 0;

    while (tab[i])
        i++;
    return i;
}
static void tab_free(char **tab) {
    int i = 0;

    while (tab[i]) {
        free(tab[i]);
        i++;
    }
    free(tab);
}
static char **tab_join(char **tab, char *line) {
    char **ret = NULL;
    int len = 0;
    int i = 0;

    len = tab_len(tab);
    // printf("len = %d\n", len);
    ret = (char**)malloc((sizeof(char*) * (len + 2)));
    while (tab[i])
    {
        ret[i] = strdup(tab[i]);
        i++;
    }
    ret[i] = strdup(line);//en peut juste pointer cas on ne le change pas
    i++;
    ret[i] = NULL;
    // tab_free(tab);
    return ret;
}

char **get_qst(void) {
    char **tab;
    char *line = NULL;
    int ret = 0;
    int fdqst;

    fdqst = open("question.txt", O_RDONLY);
    tab = (char**)malloc(sizeof(char*) * 1);
    tab[0] = NULL;
    ret = get_next_line(fdqst, &line);
	while (ret > 0)
	{
        // printf("%s\n", line);
        char **tmp = tab;
		tab = tab_join(tab, line);
        tab_free(tmp);
		free(line);
		ret = get_next_line(fdqst, &line);
	}
	free(line);
    close(fdqst);
    return tab;
}

char **get_ans(void) {
    char **tab;
    char *line = NULL;
    int ret = 0;
    int fdans;

    fdans = open("answer.txt", O_RDONLY);
    tab = (char**)malloc(sizeof(char*) * 1);
    tab[0] = NULL;
    ret = get_next_line(fdans, &line);
	while (ret > 0)
	{
        // printf("%s\n", line);
        char **tmp = tab;
		tab = tab_join(tab, line);
        tab_free(tmp);
		free(line);
		ret = get_next_line(fdans, &line);
	}
	free(line);
    close(fdans);
    return tab;
}