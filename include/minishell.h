#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "builtins.h"
# include <fcntl.h> // For open flags
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>

// libft
# include "../lib/libft/libft.h"

# define RUNNING_COMMAND 0
# define WAIT_FOR_COMMAND 1
# define HEREDOC 2
# define FD_UNSET "-42"

// ANSI COLORS
# define ANSI_COLOR_GREEN "\x1B[32m"
# define ANSI_COLOR_DEFAULT "\x1B[0m"

extern volatile int	global_signal;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				*index;
	struct s_env	*next;
}					t_env;

typedef struct s_env_pack
{
	t_env			*sys_envlist;
	t_env			*original_env;
}					t_env_pack;

// clean_utility.c
void				clean_array(char **array);
void				clean_out_all(t_env *env1, t_env *env2, char *str1,
						char *str2);
t_env				*cleanup_env(t_env *env_list);

// chang_mode.c
int					change_mode(int mode);

// main.c
void				clean_out_all(t_env *env1, t_env *env2, char *str1,
						char *str2);

// command_sighandler.c
void				running_command_sighandler(int signal);

// set_start.c
int					is_same_value(char *s1, char *s2);
t_env				*remove_node(t_env *head, t_env *node);
t_env				*set_start(t_env *env_list);

// custom_export.c
void				attatch_node(t_env **env_list, char *key, char *value);
t_env				*node_finder(t_env *env_list, char *key);
t_env				*custom_export(t_env *env_list, char *key, char *value);

// extract_env_list.c
t_env				*extract_env_list(char **envp);

// env_list_creator.
t_env				*create_env_list(int env_count);

// utility1.c
char				*find_value_from_env(t_env *env_list, char *key);
int					arrlen(void **arr);

// init_env_pack.c
char				*init_getpid(void);
t_env_pack			init_env_pack(char **envp, char *cur_dir);

// minishell.c
void				minishell(t_env_pack env_pack);

// Minji

# define SUCCESS 0
# define FAILURE 1

#endif
