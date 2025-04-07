#ifndef MINISHELL.H
# define MINISHELL.H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	int				index;
	struct s_env	*next;
} t_env;

typedef struct s_env_pack
{
	t_env	*env;
	t_env	*original_env;
}			t_env_pack;

// utility.c
void clean_array(char **array)

// main.c
void clean_out_all(t_env *env1, t_env *env2, char *str1, char *str2)

# endif