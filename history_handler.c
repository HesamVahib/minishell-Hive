#include "./include/minishell.h"

static int create_history_fd(char *root)
{
    int history_fd;
    char *file_address;

    file_address = ft_strjoin(root, "/.cmd_history");
    if (!file_address)
        return (-1);
    history_fd = open(file_address, O_RDWR | O_CREAT | O_APPEND, 0644);
    free(file_address);
    return (history_fd); // if fd is not created it becomes automatically -1

}

static int load_from_fd_history(int fd_history)
{
    char *cmd_line;
    char *trimmed;

    while ((cmd_line = get_next_line(fd_history)))
    {
        trimmed = ft_strtrim(cmd_line, "\n");
        free(cmd_line);
        if (!trimmed)
            return (1);
        add_history(trimmed);
        free(trimmed);
    }
    return (0);
}


int history_handler(char *root)
{
    int fd_history;

    fd_history = create_history_fd(root);
    if (fd_history == -1)
        return (1);
    if (load_from_fd_history(fd_history))
        return (1);
    if (close(fd_history) == -1)
        return (1);
    return (0);
}