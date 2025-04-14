#include "include/minishell.h"

static void restore_fd(t_env_pack env_pack, int std_fd, char *key)
{
    char *fd_value;
    int cur_fd;

    fd_value = value_finder(env_pack.mshell_env, key);
    cur_fd = ft_atoi(fd_value); // saved current value in cur_fd in digits
    if (fd_value)
    {
        cur_fd = ft_atoi(fd_value);
        if (cur_fd >= 0)
        {
            if (std_fd != STDIN_FILENO) // we dont want to close STDIN since we are doing something with that
                if (close(std_fd) == -1)
                    clean_out_all(env_pack.mshell_env, env_pack.sys_envlist, NULL, NULL);
            if (dup2(cur_fd, std_fd) == -1) // dup2 will overwrite the old one by new one even if it is not closed in order to restore the main ones.
                clean_out_all(env_pack.mshell_env, env_pack.sys_envlist, NULL, NULL);
        }
    }
}

void    restore_std_fd(t_env_pack env_pack)
{
    restore_fd(env_pack, STDIN_FILENO, "fd_stdin");
    restore_fd(env_pack, STDOUT_FILENO, "fd_stdout");
    restore_fd(env_pack, STDERR_FILENO, "fd_stderr");
}