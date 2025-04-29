#include "./include/minishell.h"

char *double_backslash_remover(char *cmd_line)
{
    int i;
    char *new_str;

    i = 0;
    new_str = ft_strdup("");
    while (cmd_line[i])
    {
        if(cmd_line[i] == '\\' && (cmd_line[i + 1]) && ((cmd_line[i + 1]) == '\\' || cmd_line[i + 1] == '$'))
            i++;
        new_str = append_char(new_str, cmd_line[i]);
        i++;
    }
    return (new_str);
}