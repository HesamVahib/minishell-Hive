#include "include/minishell.h"

void exit_run(t_env *env)
{
    int exit_code;

    printf(SHELL_PROMPT"\n");
    exit_code = ft_atoi(value_finder(env, "exit_code"));
    cleanup_env(env);
    if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit(1);
	if (change_mode(RUNNING_COMMAND))
		exit(1);
	exit(exit_code);

}

void exit_preparation(t_env_pack env_pack)
{
    cleanup_env(env_pack.sys_envlist);
    exit_run(env_pack.original_env);
}