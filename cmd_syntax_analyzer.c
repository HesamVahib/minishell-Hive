#include "include/minishell.h"

char **syntax_analyzer(char **tokenz)
{
    int i;

    i = 0;
    while (tokenz[i])
    {
        if (!ft_strncmp(tokenz[i], "<<", 2) || !ft_strncmp(tokenz[i], ">>", 2)
            || !ft_strncmp(tokenz[i], "<", 1) || !ft_strncmp(tokenz[i], ">", 1))
        {
            if (!tokenz[i + 1]||
                !ft_strncmp(tokenz[i + 1], "<<", 2) || !ft_strncmp(tokenz[i + 1], ">>", 2) ||
                !ft_strncmp(tokenz[i + 1], "<", 1) || !ft_strncmp(tokenz[i + 1], ">", 1) ||
                !ft_strncmp(tokenz[i + 1], "|", 1))
                return (NULL);
        }
        i++;
    }
    return (tokenz);
}