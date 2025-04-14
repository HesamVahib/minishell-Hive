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

char **line_tokenized(char *line)
{
    return(ft_split(line, ' '));
}

void    minishell(t_env_pack env_pack)
{
    char    *line;
    char    **tokenz;

    while (1)
    {
        if (change_mode(WAIT_FOR_COMMAND))
            clean_out_all(env_pack.sys_envlist, env_pack.mshell_env, NULL, NULL);
        line = readline(SHELL_PROMPT); // there is a problem with ctrl+c cuz when you prompt it it does not show the name of shell just after writing somethings it appears!
         // it can be modified
        if (!line)
            exit_preparation(env_pack);
        // printf("line is: %s\n", line);
        if (executable(line))
        {
            add_history(line);
            env_pack = export_std_fd(env_pack); // setting fd to the std fds to have a space to write and display
            printf("\n%s\n", line);
            printf("Execution\n");
            tokenz = line_tokenized(line);
            // syntaxt analyzer
            // parser
            while (*tokenz)
            {
                printf("%s\n", *tokenz++);
            }
            // free_array(&tokenz); // should be transferred to the first pointer
            restore_std_fd(env_pack); // reset the the fd's to get back to the default one if something like | (pipe) had appled on std's
        }
        free(line);
    }
}