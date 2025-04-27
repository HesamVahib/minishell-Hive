#include "./include/minishell.h"

static int open_heredoc_file(char *limiter, char **filename)
{
    int fd;

    *filename = ft_strjoin(limiter, ".txt");
    if (!(*filename))
        return (-1);
    fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return (-1);
    return (fd);
}

static void write_heredoc_content(int fd, char *limiter)
{
    char *line;
    char *temp;

    line = readline("> ");
    while (line && ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
    {
        temp = ft_strjoin(line, "\n");
        if (temp)
            write(fd, temp, ft_strlen(line) + 1);
        free(line);
        free(temp);
        line = readline("> ");
    }
    free(line);
}

char *open_heredoc(char **limiters)
{
    int fd;
    char *filename;
    int i;

    i = 0;
    filename = NULL;
    rl_on_new_line();
    rl_replace_line("", 0);
    while (limiters[i] != NULL)
    {
        if (filename)
        {
            remove(filename);
            free(filename);
        }
        fd = open_heredoc_file(limiters[i], &filename);
        if (fd == -1)
            return (free(filename), NULL);
        write_heredoc_content(fd, limiters[i]);
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