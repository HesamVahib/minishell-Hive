#include "minishell.h"

static t_env cleanup_env(t_env *env_list)
{
    t_env *temp;
    while (env_list)
    {
        temp = env_list->next;
        free(env_list->key);
        free(env_list->value);
        free(env_list);
        env_list = temp;
    }
    return (NULL);
}

int array_len(char **array)
{
    int i = 0;
    while (array[i])
        i++;
    return i;
}

t_env *extract_env_list(char **envp)
{
    t_env *env_list;
    int i;
    int env_count;
    char **temp;
    t_env *temp_env;

    env_count = array_len(envp); // function to count the number of environment variables
    env_list = create_env_list(env_count); // function to create an empty environment list
    if (!env_list)
        return (NULL); // handle error if create_env_list fails
    i = 0;
    temp_env = env_list;
    while (i < env_count)
    {
        temp = ft_split(envp[i], '='); // function to split the environment variable into key and value
        if (!temp)
            return (cleanup_env(env_list), NULL);
        temp_env->key = ft_strdup(temp[0]);
        temp_env->value = ft_strdup(temp[1]);
        clean_array(temp);
        if(!temp_env->key || !temp_env->value)
            return (cleanup_env(env_list), NULL);
        temp_env->index = i;
        temp_env= temp_env->next;
        i++;
    }
    temp_env->next = NULL;
    return (env_list);
}
