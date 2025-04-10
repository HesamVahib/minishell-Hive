/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 16:35:32 by michoi            #+#    #+#             */
/*   Updated: 2025/01/05 01:03:55 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while ((s) && (s[i]))
		i++;
	return (i);
}

int	get_idx(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	if (!dest || !src)
		return (0);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*substr;
	size_t	i;

	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	if ((!s) || (start >= ft_strlen(s)))
	{
		substr = malloc(1);
		if (!substr)
			return (0);
		substr[0] = '\0';
		return (substr);
	}
	substr = malloc(len + 1);
	if (!substr)
		return (0);
	i = 0;
	while ((s[start + i]) && (i < len))
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (free(s1), (char *)0);
	if (s1)
	{
		while (s1[i])
		{
			new_str[i] = s1[i];
			i++;
		}
		free(s1);
	}
	j = 0;
	if (s2)
	{
		while (s2[j])
			new_str[i++] = s2[j++];
	}
	new_str[i] = '\0';
	return (new_str);
}
