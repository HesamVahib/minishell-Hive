#include "include/minishell.h"

static int pipe_counter(char **tokenz)
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

    // printf("type: %s\n", type);
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
    // printf("files are not read\n");
    return (0);
}

t_cmd *cmd_args_extractor(char **tokenz)
{
    t_cmd *cmd_list;
    int n_pipe = pipe_counter(tokenz);
    int i;
    int k;
    int arg_start;
    int argc;
    cmd_list = ft_calloc(n_pipe + 1, sizeof(t_cmd));
    t_cmd *cur = &cmd_list[0];

    
    init_cmd_list(cmd_list, n_pipe);

    i = 0;
    while (tokenz[i])
    {
        if (ft_strncmp(tokenz[i], "<", 1) == 0 && tokenz[i][1] != '<')
        {
            cur->infile = ft_strdup(tokenz[++i]);
            if (!open_create_files(cur->infile, "infile"))
                printf("error on opening the infile/ should be handled better\n");

        }
        else if (ft_strncmp(tokenz[i], ">", 1) == 0 && tokenz[i][1] != '>')
        {
            cur->outfile = ft_strdup(tokenz[++i]);
            if (!open_create_files(cur->outfile, "outfile"))
                printf("error on opening the outfiles (in NOT appended)/ should be handled better\n");
            cur->append = 0;
        }
        else if (ft_strncmp(tokenz[i], ">>", 2) == 0)
        {
            cur->outfile = ft_strdup(tokenz[++i]);
            if (!open_create_files(cur->outfile, "outfile"))
                printf("error on opening the outfiles (in appended)/ should be handled better\n");
            cur->append = 1;
        }
        else if (ft_strncmp(tokenz[i], "<<", 2) == 0)
        {
            if (!tokenz[i + 1])
                return (printf("syntax error near unexpected token `newline'\n"), NULL);
            cur->is_heredoc = ft_strdup(tokenz[++i]);
        }
        else if (ft_strncmp(tokenz[i], "|", 1) == 0)
        {
            cur->is_piped = 1;
            cur = cur->next;
        }
        else
        {
            arg_start = i;
            argc = 0;
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
            k = 0;
            while (k < argc)
            {
                cur->argv[k] = ft_strdup(tokenz[arg_start + k]);
                k++;
            }
                
            cur->argv[argc] = NULL;
            continue;
        }
        i++;
    }
    return cmd_list;
}