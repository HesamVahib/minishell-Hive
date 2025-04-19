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
    char    **tokenz;
    t_cmd   *cmd_args;

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
            printf("%s\n\n", line);
            printf("Execution...\n\n");
            tokenz = line_tokenized(line);
            // int i = 0;
            // while (tokenz[i])
            // {
            //     printf("token[%d]: %s\n", i, tokenz[i]);
            //     i++;
            // }
            // exit(1);
            // April 14th
            // Lexer -- implemented
            // syntaxt analyzer like || error
            
            tokenz = syntax_analyzer(tokenz);
            if (!tokenz)
            {
                printf("syntax is not correct\n");
                exit(1);
            }
            // April 16th

            // expansion
            tokenz = dollar_expansion(tokenz, env_pack.mshell_env);
            if (!tokenz)
            {
                printf("Dollar Expnsion failed\n");
                exit(1);
            }
            // April 17th
            // parser
            cmd_args = cmd_args_extractor(tokenz);
            // April 15th
            print_cmd_temp(cmd_args);
            // free_array(&tokenz); // should be transferred to the first pointer
            restore_std_fd(env_pack); // reset the the fd's to get back to the default one if something like | (pipe) had appled on std's
        }
        free(line);
    }
}