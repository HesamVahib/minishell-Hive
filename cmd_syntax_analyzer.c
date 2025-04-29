#include "include/minishell.h"

char **syntax_analyzer(char **tokenz)
{
    int i;

    i = 0;
    while (tokenz[i]) // the last token should be returned if there is a problem
    {
        if (!ft_strncmp(tokenz[i], "|", 1) && i == 0)
            return (printf("syntax error near unexpected token `%s'\n", tokenz[i]), NULL);
        if (!ft_strncmp(tokenz[i], "<<", 2) || !ft_strncmp(tokenz[i], ">>", 2)
            || !ft_strncmp(tokenz[i], "<", 1) || !ft_strncmp(tokenz[i], ">", 1)
            || !ft_strncmp(tokenz[i], "|", 1) || !ft_strncmp(tokenz[i], ";", 1))
        {
            if (!tokenz[i + 1]||
                !ft_strncmp(tokenz[i + 1], "<<", 2) || !ft_strncmp(tokenz[i + 1], ">>", 2) ||
                !ft_strncmp(tokenz[i + 1], "<", 1) || !ft_strncmp(tokenz[i + 1], ">", 1) ||
                !ft_strncmp(tokenz[i + 1], "|", 1) || !ft_strncmp(tokenz[i], ";", 1))
                {
                    if (!tokenz[i + 1])
                        return (printf("syntax error near unexpected token `newline'\n"), NULL);
                    return (printf("syntax error near unexpected token `%s'\n", tokenz[i + 1]), NULL);
                }
        }
        i++;
    }
    return (tokenz);
}