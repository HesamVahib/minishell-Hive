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

char *open_heredoc(char **limiters)
{
    char *line;
    int i;
    int fd;
    char *filename;

    i = 0;
    // write(STDOUT_FILENO, "\n", 1); // print out a newline
    rl_on_new_line(); // move the cursor to the new line
    rl_replace_line("", STDIN_FILENO);
    while(limiters[i] != NULL)
    {
        if (filename)
        {
            remove(filename);
            free(filename);
        }
        filename = ft_strjoin(limiters[i], ".txt");
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            return (free(filename), NULL);
        line = readline("> ");
        while (ft_strncmp(line, limiters[i], ft_strlen(limiters[i])) != 0)
        {
            write(fd, ft_strjoin(line, "\n"), ft_strlen(line) + 1);
            line = readline("> ");
        }
        free(line);
        close(fd);
        i++;
    }
    return (filename);
}


int is_heredoc(t_cmd *cmd_args)
{
    int i;
    t_cmd *temp;
    char *txt_filename;

    i = 0;
    temp = cmd_args;
    txt_filename = NULL;
    while (temp)
    {
        if (temp->is_heredoc == NULL)
            return (0);
        temp = temp->next;
    }
    temp = cmd_args;
    while(temp->is_heredoc != NULL)
    {
        if (txt_filename)
            remove(txt_filename);
        txt_filename = open_heredoc(temp->heredoc_limiters);
        temp = temp->next;
    }
    return (1);
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
        if (executable(line))
        {
            add_history(line);
            env_pack = export_std_fd(env_pack); // setting fd to the std fds to have a space to write and display

            tokenz = line_tokenized(line, env_pack.mshell_env);
            if (tokenz)
            {
                cmd_args = cmd_args_extractor(tokenz);
                print_cmd_temp(cmd_args);
            }
            else
            {
                init_cmd_list(cmd_args, 0);
                printf("something HAPPENED in tokenization\n");
            }
            is_heredoc(cmd_args);
            printf("\n\nExecution...\n\n");
            restore_std_fd(env_pack); // reset the the fd's to get back to the default one if something like | (pipe) had appled on std's
        }
        free(line);
    }
}