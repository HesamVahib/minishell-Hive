#include "minishell.h"

volatile int	global_signal;

void clean_out_all(t_env *env1, t_env *env2, char *str1, char *str2)
{
    if (env1)
        cleanup_env(env1);
    if (env2)
        cleanup_env(env2);
    if (str1)
        free(str1);
    if (str2)
        free(str2);
    if (signal(SIGINT, SIG_DFL) == SIG_ERR) // for Ctrl-C to return back Ctrl+C to its default functionality
        exit(1);
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR) // for Ctrl+Back Slash
        exit(1);
    if (change_mode(RUNNING_COMMAND)) // 
		exit(1);
    exit(1);
}

char *init_getpid(void)
{
    int pid;
    char *char_pid;

    pid = getpid();
    if (pid <= 0)
    {
        char_pid = ft_strdup("$$");
        if (!char_pid)
            return (NULL);
        return (char_pid);
    }
    else
    {
        char_pid = ft_itoa(pid);
        if (!char_pid)
            return (NULL);
        return (char_pid);
    }
}

t_env_pack init_env_pack(char **envp, char *cur_dir)
{
    t_env_pack env_pack;
    t_env *env_list;
    t_env *minishell_env_list;
    char *init_pid;

    minishell_env_list = NULL;
    env_list = NULL;
    minishell_env_list = extract_env_list(envp); // thisi is the originasl one from oldpwd, creating the env by spliting the original environment into keys and values. it's gonna be used for Minishell
    env_list = extract_env_list(envp); // 
    if (!env_list || !minishell_env_list)
        clean_out_all(env_list, minishell_env_list, cur_dir, NULL);
    env_list = set_start(env_list); // whenever you open a session it starts from 1 and we want to indicate that is the nested shell or main shell. and also we clean oldpwd. we want to keep the track og main env
    if (!env_list)
        clean_out_all(env_list, minishell_env_list, cur_dir, NULL);
    /// 8th April
    minishell_env_list = custom_export(minishell_env_list, "fd_stdin", FD_UNSET);
    minishell_env_list = custom_export(minishell_env_list, "fd_stdout", FD_UNSET);
    minishell_env_list = custom_export(minishell_env_list, "fd_stderr", FD_UNSET);
    minishell_env_list = custom_export(minishell_env_list, "root", cur_dir);
    free(cur_dir);
    init_pid = init_getpid();
    if (!init_pid)
        clean_out_all(env_list, minishell_env_list, cur_dir, NULL);
    minishell_env_list = custom_export(minishell_env_list, "pid", init_pid);
    minishell_env_list = custom_export(minishell_env_list, "pid", ft_itoa(0));
    env_pack.original_env = minishell_env_list;
    return (env_pack);
}

int main(int ac, char **av, char **envp)
{
    char *cur_dir;
    int fd_in;
    int fd_out;
    t_env_pack env_pack;


    cur_dir = NULL;
    cur_dir = getcwd(NULL, 0); // get the current working directory
    if (!cur_dir)
        return (1); // handle error if getcwd fails
    fd_in = dup(STDIN_FILENO); // duplicate stdin
    fd_out = dup(STDOUT_FILENO); // duplicate stdout
    if (fd_in == -1 || fd_out == -1) // check for errors in dup
        return (free(cur_dir), 1);
    env_pack = init_env_pack(envp, cur_dir);
    // April 9th
      
    

}