#include "./include/minishell.h"

static void sigint_handler_heredoc(int sig)
{
    (void)sig;
    global_signal = SIGINT;
}

static int open_heredoc_file(char *limiter, char **filename)
{
    int fd;
	// 🌟 don't even need limiter and filename for this funtion?
	(void)limiter;
	*filename = "smth";
    // *filename = ft_strjoin(limiter, ".txt");
    if (!(*filename))
        return (-1);
	/* 🌟 O_TMPFILE: create an unnamed temporary regular file.
			The pathname argument specifies a directory.
			Anything written to the resulting file will be lost when the last file descriptor is closed, unless the file is given a name.
	*/
    fd = open("./", O_WRONLY | O_TMPFILE, 0644);
	if (fd == -1)
        return (-1);
    return (fd);
}

static void write_heredoc_content(int fd, char *limiter)
{
    char *line;
    char *temp;

    signal(SIGINT, sigint_handler_heredoc);
    rl_event_hook = sig_handler_heredoc;
    while (1)
    {
        line = readline("> ");
        if (!line || global_signal == SIGINT)
            break ;
        if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
        {
            free(line);
            break;
        }
        temp = ft_strjoin(line, "\n");
        if (temp)
            write(fd, temp, ft_strlen(temp));
        free(line);
        free(temp);
    }
	// 🌟 this statement caused double free. Did you want to check if line variable is exactly NULL?
    // if (line)
    //     free(line);
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
        printf("in open\n");
        if (filename)
        {
			// 🌟 remove - forbidden function!!!
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

int is_all_heredoc(t_cmd *cmd)
{
    while (cmd)
    {
        if (cmd->is_heredoc == NULL)
            return (0);
        cmd = cmd->next;
    }
    return (1);
}

int heredoc_processing(t_cmd *cmd_args)
{
    t_cmd *temp;
    char *txt_filename;

    temp = cmd_args;
    txt_filename = NULL;
    if (!is_all_heredoc(temp))
        return (0);
    while(cmd_args && cmd_args->is_heredoc)
    {
		// 🌟 remove - forbidden function!!!
        if (txt_filename)
            remove(txt_filename);
        txt_filename = open_heredoc(cmd_args->heredoc_limiters);
        if (global_signal == SIGINT)
        {
			// 🌟 remove - forbidden function!!!
            if (txt_filename)
                remove(txt_filename);
            rl_event_hook = NULL;
            return (free(txt_filename), 0);
        }
        cmd_args = cmd_args->next;
    }
    rl_event_hook = NULL;
    return (1);
}
