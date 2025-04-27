#include "include/minishell.h"

t_env	*extract_env_list(char **envp)
{
	t_env	*env_list;
	int		i;
	int		env_count;
	char	**temp;
	t_env	*temp_env;

	env_count = arrlen(envp);
	env_list = create_env_list(env_count);
	if (!env_list)
		return (printf("env_list is null"), NULL);
	i = 0;
	temp_env = env_list;
	while (i < env_count)
	{
		temp = ft_split(envp[i], '=');
		if (!temp)
			return (cleanup_env(env_list), NULL);
		temp_env->key = ft_strdup(temp[0]);
		temp_env->value = ft_strdup(temp[1]);
		if (!temp_env->key || !temp_env->value)
			return (cleanup_env(env_list), NULL);
		temp_env = temp_env->next;
		i++;
	}
	return (env_list);
}
