#include "include/minishell.h"

t_env	*extract_env_list(char **envp)
{
	t_env	*env_list;
	int		i;
	int		env_count;
	char	**temp;
	t_env	*temp_env;

	env_count = arrlen(envp);
		// function to count the number of environment variables
	env_list = create_env_list(env_count);
		// function to create an empty environment list
	if (!env_list)
		return (printf("env_list is null"), NULL);
			// handle error if create_env_list fails
	i = 0;
	temp_env = env_list;
	// printf("testhi: %s\n", temp_env->key);
	while (i < env_count)
	{
		temp = ft_split(envp[i], '=');
			// function to split the environment variable into key and value
		if (!temp)
			return (cleanup_env(env_list), NULL);
		temp_env->key = ft_strdup(temp[0]);
		temp_env->value = ft_strdup(temp[1]);
		// clean_array(temp);
		if (!temp_env->key || !temp_env->value)
			return (cleanup_env(env_list), NULL);
		// *(temp_env->index) = i;
		temp_env = temp_env->next;
		i++;
	}
	// env_list = temp_env;
	// while (env_list)
	// {
	//     // printf("%s, %s\n", env_list->key, env_list->value);
	//     env_list = env_list->next;
	// }
	// exit (1);
	return (env_list);
}
