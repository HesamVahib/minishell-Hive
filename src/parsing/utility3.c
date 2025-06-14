/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:43:09 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 16:43:44 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	arrlen(char **arr)
{
	int	len;

	if (!arr || !*arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

int	update_node(t_env *env, char *key, char *new_value)
{
	t_env	*node;
	char	*temp;

	node = node_finder(env, key);
	if (!node)
		return (FAILURE);
	temp = ft_strdup(new_value);
	if (!temp)
		return (FAILURE);
	free(node->value);
	node->value = temp;
	return (SUCCESS);
}
