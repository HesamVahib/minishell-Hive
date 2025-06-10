<<<<<<< HEAD:set_start.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:42:21 by hvahib            #+#    #+#             */
/*   Updated: 2025/05/11 21:57:06 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	is_same_value(char *s1, char *s2)
{
	if ((ft_strlen(s1) == ft_strlen(s2)) && (!ft_strncmp(s1, s2,
				ft_strlen(s1))))
		return (1);
	return (0);
}

t_env	*remove_node(t_env *head, t_env *node)
{
	t_env	*temp;
	t_env	*temp_head;
	t_env	*previous_node;

	temp_head = head;
	if (head == node)
	{
		head = head->next;
		free(node->key);
		free(node->value);
		free(node);
		return (head);
	}
	temp = head;
	while (temp && temp != node)
	{
		previous_node = temp;
		temp = temp->next;
	}
	if (!temp)
		return head;
	previous_node->next = node->next;
	free(node->key);
	free(node->value);
	free(node);
	return (temp_head);
}

t_env	*set_start(t_env *env_list)
{
	t_env	*temp_env;

	if (find_value_from_env(env_list, "SHLVL"))
		custom_export(env_list, "SHLVL", "2");
	else
		custom_export(env_list, "SHLVL", "1");
	temp_env = env_list;
	while (temp_env && !is_same_value(temp_env->key, "OLDPWD"))
		temp_env = temp_env->next;
	if (temp_env)
		env_list = remove_node(env_list, temp_env);
	return (env_list);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:42:21 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/07 14:51:09 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_same_value(char *s1, char *s2)
{
	if ((ft_strlen(s1) == ft_strlen(s2)) && (!ft_strncmp(s1, s2,
				ft_strlen(s1))))
		return (1);
	return (0);
}

t_env	*remove_node(t_env *head, t_env *node)
{
	t_env	*temp;
	t_env	*temp_head;
	t_env	*previous_node;

	temp_head = head;
	if (head == node)
	{
		head = head->next;
		free(node->key);
		free(node->value);
		free(node);
		return (head);
	}
	temp = head;
	while (temp && temp != node)
	{
		previous_node = temp;
		temp = temp->next;
	}
	if (!temp)
		return head;
	previous_node->next = node->next;
	free(node->key);
	free(node->value);
	free(node);
	return (temp_head);
}

t_env	*set_start(t_env *env_list)
{
	t_env	*temp_env;

	if (find_value_from_env(env_list, "SHLVL"))
		custom_export(env_list, "SHLVL", "2");
	else
		custom_export(env_list, "SHLVL", "1");
	temp_env = env_list;
	while (temp_env && !is_same_value(temp_env->key, "OLDPWD"))
		temp_env = temp_env->next;
	if (temp_env)
		env_list = remove_node(env_list, temp_env);
	return (env_list);
}
>>>>>>> 874a9b48f3199909f568ebc8744a2ebc01ae86ce:src/parsing/set_start.c
