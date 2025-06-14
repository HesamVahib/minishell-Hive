/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 22:23:34 by michoi            #+#    #+#             */
/*   Updated: 2025/06/11 16:44:53 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_sign(const char **nptr, int *sign)
{
	if (**nptr == '-' || **nptr == '+')
	{
		if (**nptr == '-')
			*sign *= -1;
		(*nptr)++;
	}
}

static void	check_nbr_in_range(int sign, long long num, char digit,
		int *err_flag)
{
	if (sign == -1)
	{
		if ((unsigned)num > (LLONG_MAX / 10 + (1 - (digit - 48)) / 10))
			*err_flag = UNDERFLOW;
	}
	else
	{
		if (num > (LLONG_MAX - (digit - 48)) / 10)
			*err_flag = OVERFLOW;
	}
}

long long	ft_atoll(const char *nptr, int *range_error)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	if (!nptr || !*nptr)
		return (res);
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	check_sign(&nptr, &sign);
	while (*nptr && ft_isdigit(*nptr))
	{
		check_nbr_in_range(sign, res, *nptr, range_error);
		if (*range_error == UNDERFLOW)
			return (LLONG_MIN);
		else if (*range_error == OVERFLOW)
			return (LLONG_MAX);
		res = res * 10 + (*nptr - 48);
		nptr++;
	}
	res *= sign;
	return (res);
}
