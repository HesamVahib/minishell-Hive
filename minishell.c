#include "./include/minishell.h"

void    minishell(t_env_pack env_pack)
{
    char    *line;

    while (1)
    {
        if (change_mode(WAIT_FOR_COMMAND))
            clean_out_all(env_pack.sys_envlist, env_pack.original_env, NULL, NULL);
        line = readline(ANSI_COLOR_GREEN"[(what the)shell]$ "ANSI_COLOR_DEFAULT); // it can be modified
        
        printf("line is: %s\n", line);
        add_history(line);
        free(line);
    }
}