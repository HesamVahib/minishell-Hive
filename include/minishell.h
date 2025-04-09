#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "builtins.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>

# define RUNNING_COMMAND 0
# define WAIT_FOR_COMMAND 1
# define HEREDOC 2

extern volatile int	global_signal;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				index;
	struct s_env	*next;
}					t_env;

typedef struct s_env_pack
{
	t_env			*env;
	t_env			*original_env;
}					t_env_pack;

// utility.c
void				clean_array(char **array);

// chang_mode.c
int					change_mode(int mode);

// main.c
void				clean_out_all(t_env *env1, t_env *env2, char *str1,
						char *str2);

// Minji

# define SUCCESS 0
# define FAILURE 1

#endif
