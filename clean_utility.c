#include "include/minishell.h"


// in libft, there's free_array function
/*
void clean_array(char **array)
{
    int i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
*/

t_env *cleanup_env(t_env *env_list)
{
    t_env *temp;
    
    while (env_list)
    {
        temp = env_list->next;
        free(env_list->key);
        free(env_list->value);
        free(env_list->index);
        free(env_list);
        env_list = temp;
    }
    return (env_list);
}

void clean_out_all(t_env *env1, t_env *env2, char *str1, char *str2)
{
    if (env1)
        cleanup_env(env1);
    if (env2)
        cleanup_env(env2);
    if (str1)
        free(str1);
    if (str2)
        free(str2);
    if (signal(SIGINT, SIG_DFL) == SIG_ERR) // for Ctrl-C to return back Ctrl+C to its default functionality
        exit(1);
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) // for Ctrl+Back Slash
        exit(1);
    if (change_mode(RUNNING_COMMAND)) //
		exit(1);
    exit(1);
}
