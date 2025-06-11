/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:21:18 by michoi            #+#    #+#             */
/*   Updated: 2024/11/06 16:37:13 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!little[j])
		return ((char *)big);
	while ((i < len) && big[i])
	{
		while (((i + j) < len) && (big[i + j] == little[j]) && little[j])
			j++;
		if (!little[j])
			return ((char *)big + i);
		i++;
		j = 0;
	}
	return (0);
}
