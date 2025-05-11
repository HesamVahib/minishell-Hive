/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_creator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:37 by hvahib            #+#    #+#             */
/*   Updated: 2025/05/08 12:39:38 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_env	*create_env_node(void)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = NULL;
	new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_env	*create_env_list(int env_count)
{
	t_env	*head;
	t_env	*current;
	int		i;

	if (env_count <= 0)
		return (NULL);
	head = create_env_node();
	if (!head)
		return (NULL);
	current = head;
	i = 1;
	while (i < env_count)
	{
		current->next = create_env_node();
		if (!current->next)
			return (NULL);
		current = current->next;
		i++;
	}
	current->next = NULL;
	return (head);
}
