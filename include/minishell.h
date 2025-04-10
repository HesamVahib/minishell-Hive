#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <fcntl.h>   // For open flags


// libft
# include "../lib/libft/libft.h"


# define RUNNING_COMMAND 0
# define WAIT_FOR_COMMAND 1
# define HEREDOC 2
# define FD_UNSET "-42"

extern volatile int global_signal;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				*index;
	struct s_env	*next;
} t_env;

typedef struct s_env_pack
{
	t_env	*sys_envlist;
	t_env	*original_env;
}			t_env_pack;

// clean_utility.c
void clean_array(char **array);
void clean_out_all(t_env *env1, t_env *env2, char *str1, char *str2);
t_env *cleanup_env(t_env *env_list);

// chang_mode.c
int change_mode(int mode);

// main.c
void clean_out_all(t_env *env1, t_env *env2, char *str1, char *str2);

// command_sighandler.c
void running_command_sighandler(int signal);

// set_start.c
int same_finder(char *s1, char *s2);
t_env   *node_remover(t_env *head, t_env    *node);
t_env *set_start(t_env *env_list);

// custom_export.c
void    attatch_node(t_env **env_list, char *key, char   *value);
t_env   *node_finder(t_env *env_list, char *key);
t_env *custom_export(t_env *env_list, char *key, char *value);

// extract_env_list.c
t_env *extract_env_list(char **envp);

// env_list_creator.
t_env *create_env_list(int env_count);

// utility1.c
char *value_finder(t_env *env_list, char *key);

// Minji


# endif
