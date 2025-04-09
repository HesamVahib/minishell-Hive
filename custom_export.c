#include "minishell.h"



void    attatch_node(t_env **env_list, char *key, char   *value)
{
    t_env   *new;

    new = malloc(sizeof(t_env));
    if (!new)
    {
        *env_list = NULL;
        return ;
    }
    new->key = key;
    new->value = value;
    new->next = *env_list;
    *env_list = new; // changig the head of list to the new
}

t_env   *node_finder(t_env *env_list, char *key)
{
    t_env   *temp;

    temp = env_list;
    while (temp)
    {
        if (same_finder(temp->key, key))
            return (temp);
        temp = temp->next;
    }
    return (temp);
}

t_env *custom_export(t_env *env_list, char *key, char *value)
{
    t_env   *temp;
    char    *temp_key;
    char    *temp_value;

    temp = node_finder(env_list, key);
    if (temp)
    {
        free(temp->value);
        temp->value = ft_strdup(key);
        if (!temp->value)
            clean_out_all(env_list, NULL, NULL, NULL);
    }
    else
    {
        temp_key = ft_strdup(key);
        temp_value = ft_strdup(value);
        if (!temp_key || !temp_value)
            clean_out_all(env_list, NULL, NULL, NULL);
        attatch_node(&env_list, temp_key, temp_value);
        if (!env_list)
            clean_out_all(env_list, NULL, NULL, NULL);
    }
    return (env_list);
}