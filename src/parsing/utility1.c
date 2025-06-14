/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:43:02 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 16:43:41 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	char	*s2_part;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	s2_part = ft_strndup(s2, n);
	if (!s2_part)
		return (NULL);
	res = ft_strjoin(s1, s2_part);
	free(s2_part);
	return (res);
}

char	*extract_var_key(char *start_ptr)
{
	int	len;

	len = 0;
	while ((start_ptr[len]) && (ft_isalnum(start_ptr[len])
			|| start_ptr[len] == '_'))
		len++;
	return (ft_strndup(start_ptr, len));
}

char	*append_char(char *str, char c)
{
	char	*temp;

	if (!str)
		return (NULL);
	temp = ft_strnjoin(str, &c, 1);
	free(str);
	return (temp);
}

char	*find_value_from_env(t_env *env_list, char *key)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (is_same_value(temp->key, key))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
