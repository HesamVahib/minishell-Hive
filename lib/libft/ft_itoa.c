/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:42:06 by michoi            #+#    #+#             */
/*   Updated: 2024/11/14 22:49:28 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_chars(long n, int const base)
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	else if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n != 0)
	{
		count++;
		n /= base;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long		num;
	int			len;
	char		*result;

	num = n;
	len = count_chars(num, 10);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	result[len] = 0;
	if (num == 0)
		result[0] = '0';
	else if (num < 0)
	{
		result[0] = '-';
		num = -num;
	}
	while (num != 0)
	{
		len--;
		result[len] = (num % 10) + 48;
		num /= 10;
	}
	return (result);
}
