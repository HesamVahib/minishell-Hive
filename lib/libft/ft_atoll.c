/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 22:23:34 by michoi            #+#    #+#             */
/*   Updated: 2025/04/14 22:43:36 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <errno.h>
#include <stdio.h>
long long ft_atoll(const char *nptr)
{
	int	sign;
	long long	res;

	sign = 1;
	res = 0;
	// if (!nptr || !*nptr)
	// 	return (res);
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr && ft_isdigit(*nptr))
	{
		res = res * 10 + (*nptr - 48);
		nptr++;
	}
	//res *= sign;
	printf("%lld\n", res);
	return ((long long)res * sign);
}
int main()
{
	long long res = ft_atoll("-18446744073709551615");
	printf("res: %lld\n", res);
	if (res == LLONG_MIN || res == LLONG_MAX)
    {
        /* If the value provided was out of range, display a warning message */
        if (errno == ERANGE)
            printf("The value provided was out of range\n");
    }
}
