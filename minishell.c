#include "./include/minishell.h"

void    minishell(t_env_pack env_pack)
{
    char    *line;

    while (1)
    {
        line = readline(SHELL_PROMPT);
        if (change_mode(WAIT_FOR_COMMAND))
            clean_out_all(env_pack.sys_envlist, env_pack.original_env, NULL, NULL);
         // it can be modified
        if (!line)
            exit_preparation(env_pack);
        // printf("line is: %s\n", line);
        add_history(line);

        
        free(line);
    }
}