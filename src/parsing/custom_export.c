/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:20 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/09 18:30:54 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env_pack	std_fd_custom_exporter(t_env_pack env_pack, int fd_std, char *key)
{
	char	*std_itoa;
	int		fd;

	fd = dup(fd_std);
	if (fd == -1)
		clean_out_all(env_pack.sys_envlist, env_pack.mshell_env, NULL, NULL);
	std_itoa = ft_itoa(fd);
	if (!std_itoa)
	clean_out_all(env_pack.sys_envlist, env_pack.mshell_env, NULL, NULL);
	env_pack.mshell_env = custom_export(env_pack.mshell_env, key, std_itoa);
	free(std_itoa);
	return (env_pack);
}

t_env_pack	export_std_fd(t_env_pack env_pack)
{
	env_pack = std_fd_custom_exporter(env_pack, STDIN_FILENO, "fd_stdin");
	env_pack = std_fd_custom_exporter(env_pack, STDOUT_FILENO, "fd_stdout");
	env_pack = std_fd_custom_exporter(env_pack, STDERR_FILENO, "fd_stderr");
	return (env_pack);
}

t_env	*update_env(t_env *env_list, char *key, char *value)
{
	t_env	*new;
	t_env	*temp;

	if (!key)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!env_list->next)
	{
		env_list->next = new;
	}
	else
	{
		temp = env_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (env_list);
}

t_env	*node_finder(t_env *env_list, char *key)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (is_same_value(temp->key, key))
			return (temp);
		temp = temp->next;
	}
	return (temp);
}

t_env	*custom_export(t_env *env_list, char *key, char *value)
{
	t_env	*temp;
	char	*temp_key;
	char	*temp_value;
	
	temp_value = NULL;
	temp = node_finder(env_list, key);
	if (temp)
	{
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		if (value && *value)
		{
			temp->value = ft_strdup(value);
			if (!temp->value)
				clean_out_all(env_list, NULL, NULL, NULL);
		}
		return (env_list);
	}
	else
	{
		temp_key = ft_strdup(key);
		if (!temp_key)
			clean_out_all(env_list, NULL, NULL, NULL);
		if (value && *value)
		{
			temp_value = ft_strdup(value);
			if (!temp_value)
				clean_out_all(env_list, NULL, NULL, NULL);
		}
		env_list = update_env(env_list, temp_key, temp_value);
		if (!env_list)
			clean_out_all(env_list, NULL, NULL, NULL);
		return (env_list);
	}
}
