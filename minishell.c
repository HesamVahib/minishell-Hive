#include "./include/minishell.h"

static int executable(char *line)
{
    int i;

    if (!line || !line[0])
        return (0);
    i = 0;
    while (line[i])
    {
        if (!ft_isspace(line[i]))
            return (1);
        i++;
    }
    return (0);
}


void    minishell(t_env_pack env_pack)
{
    char    *line;

    while (1)
    {
        if (change_mode(WAIT_FOR_COMMAND))
            clean_out_all(env_pack.sys_envlist, env_pack.original_env, NULL, NULL);
        line = readline(SHELL_PROMPT); // there is a problem with ctrl+c cuz when you prompt it it does not show the name of shell just after writing somethings it appears!
         // it can be modified
        if (!line)
            exit_preparation(env_pack);
        // printf("line is: %s\n", line);
        if (executable(line))
        {
            add_history(line);
            env_pack = export_std_fd(env_pack);
            printf("\n%s\n", line);
            printf("Execution\n");
            restore_std_fd(env_pack);
        }
        free(line);
    }
}