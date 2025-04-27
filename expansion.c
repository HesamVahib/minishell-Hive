#include "include/minishell.h"


static int dollar_validated(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if((str[i] == '$' && str[i + 1] && str[i + 1] == '\'') && (str[i - 1] && str[i - 1] != '$'))
            return (0);
        i++;
    }
    return (1);
}

char *stitch_strings(char **temp_split)
{
    int i;
    char *result;

    if (!temp_split || !*temp_split)
        return NULL;
    result = ft_strdup("");
    if (!result)
        return NULL;
    i = 0;
    while (temp_split[i])
    {
        char *temp = ft_strjoin(result, temp_split[i]);
        free(result);
        if (!temp) return NULL;
        result = temp;
        i++;
    }
    return result;
}

static char *expand_single_token(char *token, t_env *env)
{
    char *new_token;

    new_token = process_dollars(token, env);
    return (new_token);
}

static char *copy_or_expand_token(char **tokenz, int i, t_env *env)
{
    char *new_token;

    if (dollar_validated(tokenz[i]) == 1)
    {
        printf("token is: %s\n", tokenz[i]);
        new_token = expand_single_token(tokenz[i], env);
        if (!new_token)
            return (NULL);
    }
    else
        new_token = ft_strdup(tokenz[i]);
    return (new_token);
}

char **dollar_expansion(char **tokenz, t_env *env)
{
    int i;
    char **res;

    res = malloc((arrlen(tokenz) + 1) * sizeof(char *));
    if (!res)
        return (NULL);
    i = 0;
    while (tokenz[i])
    {
        res[i] = copy_or_expand_token(tokenz, i, env);
        if (!res[i])
            return (NULL);
        i++;
    }
    res[i] = NULL;
    return (res);
}

