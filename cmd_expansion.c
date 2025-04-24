#include "include/minishell.h"

char *ft_strnjoin(char *s1, char *s2, size_t n)
{
    char *s2_part;
    char *res;

    if (!s1 || !s2)
        return (NULL);
    s2_part = ft_strndup(s2, n);
    if (!s2_part)
        return (NULL);
    res = ft_strjoin(s1, s2_part);
    free(s2_part);
    return (res);
}

char *extract_var_key(char *start_ptr)
{
    int len;
    
    len = 0;
    while ((start_ptr[len]) && (ft_isalnum(start_ptr[len]) || start_ptr[len] == '_'))
        len++;
    return ft_strndup(start_ptr, len);
}

char *append_char(char *str, char c)
{
    char *temp;

    temp = ft_strnjoin(str, &c, 1);
    free(str);
    return (temp);
}

char *process_dollars(char *token, t_env *env)
{
    char *res;
    char *str;
    char *var_key;
    char *var_value;
    int i;
    pid_t pid;

    res = ft_strdup("");
    str = token;
    i = 0;
    while (str[i])
    {
        if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i] == '_'))
        {
            var_key = extract_var_key(&str[i + 1]);
            var_value = find_value_from_env(env, var_key);
            if(var_value)
                res = ft_strjoin(res, var_value);
            else
                res = ft_strjoin(res, "");
            i += ft_strlen(var_key) + 1;
            free (var_key);
        }
        else if (str[i] == '$' && str[i + 1] && str[i + 1] == '$') // implementing $$
        {
            pid = getpid();
            res = ft_strjoin(res, ft_itoa(pid));
            i += 2;
        }
        else
        {
            if (str[i] == '$' && str[i + 1] && str[i + 1] != '\'') // echo "$'HOME'" = $'HOME' not implemented
                i++;
            res = append_char(res, str[i]);
            i++;
        }
    }
    return (res);

}

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

char **dollar_expansion(char **tokenz, t_env *env)
{
    int i;
    char **res;
    char **temp;
    char *new_token;
    
    res = malloc((arrlen(tokenz) + 1) * sizeof(char *));
    if (!res)
        return (NULL);
    temp = tokenz;
    i = 0;
    while(temp[i])
    {
        if (dollar_validated(temp[i]) == 1)
        {
            printf("token is: %s\n", temp[i]);
            new_token = process_dollars(tokenz[i], env);
            if (!new_token)
                return (NULL);
            res[i] = new_token;
        }
        else
            res[i] = tokenz[i];
        i++;
    }
    res[i] = NULL;
    return (res);
}
