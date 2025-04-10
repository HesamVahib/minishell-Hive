#include "include/minishell.h"

char *value_finder(t_env *env_list, char *key)
{
    t_env *temp;

    temp = env_list;
    while (temp)
    {
        if (same_finder(temp->value, key))
            return(temp->value);
        temp = temp->next;
    }
    return (NULL);
}