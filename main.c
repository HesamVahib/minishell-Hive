#include "./include/minishell.h"

volatile int	global_signal;

int main(int ac, char **av, char **envp)
{
    char *cur_dir;
    int fd_in;
    int fd_out;
    t_env_pack env_pack;


    (void)ac;
    (void)av;
    cur_dir = NULL;
    cur_dir = getcwd(NULL, 0); // get the current working directory
    if (!cur_dir)
        return (1); // handle error if getcwd fails
    fd_in = dup(STDIN_FILENO); // duplicate stdin
    fd_out = dup(STDOUT_FILENO); // duplicate stdout
    if (fd_in == -1 || fd_out == -1) // check for errors in dup
        return (free(cur_dir), 1);
    env_pack = init_env_pack(envp, cur_dir);
    minishell(env_pack);
    printf("\n\nfinished\n\n");
    return (0);
}
