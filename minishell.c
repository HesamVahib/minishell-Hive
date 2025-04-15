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

int pipe_counter(char **tokenz)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (tokenz[i])
    {
        if (tokenz[i][j] == '|')
            j++;
        i++;
    }
    return (j);
}

t_cmd *cmd_args_extractor(char **tokenz)
{
    t_cmd *cmd_list;
    int n_pipe = pipe_counter(tokenz);
    int i;
    cmd_list = ft_calloc(n_pipe + 1, sizeof(t_cmd));
    t_cmd *cur = &cmd_list[0];

    
    int k = 0;
    while (k < n_pipe) // init pointers
    {
        cmd_list[k].next = &cmd_list[k + 1];
        cmd_list[k + 1].previous = &cmd_list[k];
        k++;
    }

    i = 0;
    while (tokenz[i])
    {
        if (ft_strncmp(tokenz[i], "<", 1) == 0 && tokenz[i][1] != '<')
            cur->infile = ft_strdup(tokenz[++i]);
        else if (ft_strncmp(tokenz[i], ">", 1) == 0 && tokenz[i][1] != '>')
        {
            cur->outfile = ft_strdup(tokenz[++i]);
            cur->append = 0;
        }
        else if (ft_strncmp(tokenz[i], ">>", 2) == 0)
        {
            cur->outfile = ft_strdup(tokenz[++i]);
            cur->append = 1;
        }
        else if (ft_strncmp(tokenz[i], "<<", 2) == 0)
            cur->is_heredoc = ft_strdup(tokenz[++i]);
        else if (ft_strncmp(tokenz[i], "|", 1) == 0)
        {
            cur->is_piped = 1;
            cur = cur->next;
        }
        else
        {
            int arg_start = i;
            int argc = 0;
            while (tokenz[i] && ft_strncmp(tokenz[i], "|", 1) != 0 &&
                   ft_strncmp(tokenz[i], "<", 1) != 0 &&
                   ft_strncmp(tokenz[i], ">", 1) != 0 &&
                   ft_strncmp(tokenz[i], ">>", 2) != 0 &&
                   ft_strncmp(tokenz[i], "<<", 2) != 0)
            {
                i++;
                argc++;
            }
            cur->argv = ft_calloc(argc + 1, sizeof(char *));
            for (int k = 0; k < argc; k++)
                cur->argv[k] = ft_strdup(tokenz[arg_start + k]);
            cur->argv[argc] = NULL;
            continue;
        }
        i++;
    }

    return cmd_list;
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
            // April 14th
            // Lexer -- implemented
            // syntaxt analyzer like || error
            // expansion
            // parser
            cmd_args = cmd_args_extractor(tokenz);
            int i = 0;
            while (cmd_args)
            {
                printf("=== Command %d ===\n", i);
                if (cmd_args->argv)
                {
                    printf("argv: ");
                    for (int j = 0; cmd_args->argv[j]; j++)
                        printf("'%s' ", cmd_args->argv[j]);
                    printf("\n");
                }
                if (cmd_args->infile)
                    printf("infile: '%s'\n", cmd_args->infile);
                if (cmd_args->outfile)
                    printf("outfile: '%s' (append: %d)\n", cmd_args->outfile, cmd_args->append);
                if (cmd_args->is_heredoc)
                    printf("heredoc limiter: '%s'\n", cmd_args->is_heredoc);
                printf("is_piped: %d\n", cmd_args->is_piped);
                printf("\n");

                cmd_args = cmd_args->next;
                i++;
            }
            // free_array(&tokenz); // should be transferred to the first pointer
            restore_std_fd(env_pack); // reset the the fd's to get back to the default one if something like | (pipe) had appled on std's
        }
        free(line);
    }
}