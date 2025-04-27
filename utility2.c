#include "include/minishell.h"

char *ft_strndup(const char *s, int n)
{
    char *dup;
    int i;

    i = 0;
    dup = malloc(n + 1);
    if (!dup)
        return NULL;
    while (i < n)
    {
        dup[i] = s[i];
        i++;
    }
    dup[n] = '\0';
    return dup;
}