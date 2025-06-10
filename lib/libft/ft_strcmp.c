<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:20:13 by michoi            #+#    #+#             */
/*   Updated: 2025/05/10 21:24:12 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 || *s2)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:20:13 by michoi            #+#    #+#             */
/*   Updated: 2025/06/07 18:06:22 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	while (*s1 || *s2)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}
>>>>>>> 874a9b48f3199909f568ebc8744a2ebc01ae86ce
