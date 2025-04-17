#include "include/minishell.h"

char **dollar_expansion(char **tokenz, t_env *env)
{
    char **temp;
    char *env_value;
    int i;
    int j;
    char *back_value;

    temp = tokenz;
    i = 0;
    while(temp[i])
    {
        j = 0;
        while(temp[i][j]) // what about [echo hesam$HOME$HOME]
        {
            printf("char is: %c\n", temp[i][j]);
            if(temp[i][j] == '$')
            {
                back_value = ft_strndup(temp[i], j);
                env_value = ft_strdup(find_value_from_env(env, temp[i] + j + 1)); // should malloc fail be handled.
                if (env_value)
                    temp[i] = ft_strdup(ft_strjoin(back_value, env_value));
                else
                    temp[i] = ft_strdup(ft_strjoin(back_value, ""));
            }
            j++;
        }
        i++;
    }
    return (temp);
}