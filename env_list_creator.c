#include "minishell.h"

create_env_node(void)
{
    t_env *new_node;

    new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    new_node->key = NULL;
    nw_node->value = NULL;
    new_node->indeex = 0;
    new_node->next = NULL;
    return (new_node);
}

t_env *create_env_list(int env_count)
{
    t_env *head;
    t_env *new;
    t_env *current;
    int i;

    if (env_count <= 0)
        return (NULL);
    i = 0;
    while (i < env_count)
    {
        head = create_env_node();
        if (!head)
            return (NULL);
        if (i == 0)
            current = head;
        else
            current->next = head;
        current = head;
        i++;
    }
    current->next = NULL;
    return (head);
}