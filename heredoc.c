#include "./include/minishell.h"

char *open_heredoc(char **limiters)
{
    char *line;
    int i;
    int fd;
    char *filename;
    char *temp;

    i = 0;
    filename = NULL;
    rl_on_new_line();
    rl_replace_line("", 0);
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
        while (line && ft_strncmp(line, limiters[i], ft_strlen(limiters[i])) != 0)
        {
            // if (global_signal == SIGINT)
            //     return (free(line), close(fd), filename);
            temp = ft_strjoin(line, "\n");
            write(fd, temp, ft_strlen(line) + 1);
            free(line);
            free(temp);
            line = readline("> ");
        }
        free(line);
        close(fd);
        i++;
    }
    return (filename);
}


int heredoc_processing(t_cmd *cmd_args, t_env_pack env_pack)
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
    if (change_mode(HEREDOC))
            clean_out_all(env_pack.sys_envlist, env_pack.mshell_env, NULL, NULL);
    while(cmd_args && cmd_args->is_heredoc)
    {
        if (txt_filename)
            remove(txt_filename);
        txt_filename = open_heredoc(cmd_args->heredoc_limiters);
        cmd_args = cmd_args->next;
    }
    return (1);
}