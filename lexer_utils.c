#include "include/minishell.h"

int pipe_counter(char **tokenz)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (tokenz[i])
    {
        if (ft_strncmp(tokenz[i], "|", 1) == 0)
            count++;
        i++;
    }
    return (count);
}

void init_cmd_list(t_cmd *cmd_list, int n_pipe)
{
    int k = 0;
    while (k <= n_pipe)
    {
        cmd_list[k].infile = NULL;
        cmd_list[k].outfile = NULL;
        cmd_list[k].append = 0;
        cmd_list[k].is_heredoc = NULL;
        cmd_list[k].heredoc_limiters = NULL;
        cmd_list[k].argv = NULL;
        cmd_list[k].is_piped = 0;

        if (k < n_pipe)
            cmd_list[k].next = &cmd_list[k + 1];
        else
            cmd_list[k].next = NULL;

        if (k > 0)
            cmd_list[k].previous = &cmd_list[k - 1];
        else
            cmd_list[k].previous = NULL;

        k++;
    }
}

int open_create_files(const char *filename, char *type)
{
    int fd;

    if (ft_strncmp(type, "outfile", 7) == 0)
    {
        fd = open(filename, O_CREAT | O_WRONLY, 0644);
        if (fd == -1)
            return (-1);
        close (fd);
        return (1);
    }
    else if (ft_strncmp(type, "infile", 6) == 0)
    {
        fd = open(filename, O_RDONLY);
        if (fd == -1)
        {
            if (errno == ENOENT)
                return(printf("%s: No such file or directory\n", filename), 0);
        }
        close (fd);
        return (1);
    }
    return (0);
}

char **limiter_collector(char **delim_list, char *new_delim)
{
    int d_list_size;
    int new_d_size;
    char **new_list;
    int i;

    d_list_size = arrlen(delim_list);
    new_d_size = ft_strlen(new_delim);
    i = 0;
    if (delim_list != NULL)
        while (delim_list[i])
            i++;
    new_list = (char **)malloc((i + 2) * sizeof(char *));
    if (!new_list)
        return (NULL);
    if (delim_list != NULL)
    {
        ft_memcpy(new_list, delim_list, i * (sizeof(char *)));
        free (delim_list);
    }
    new_list[i] = ft_strdup(new_delim);
    if (!new_list[i])
        return (free(new_list), free(delim_list), NULL);
    new_list[i + 1] = NULL;
    return(new_list);
}
