/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:19:52 by michoi            #+#    #+#             */
/*   Updated: 2025/06/01 21:24:37 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

static void	print_exit_arg_err(char *arg)
{
	print_cmd_err_with_arg("exit", arg, "numeric argument required");
}

static bool	is_numeric(char *input)
{
	if (!input || !*input)
		return (false);
	if (*input == '-' || *input == '+')
	{
		if (!ft_isdigit(*(input + 1)))
			return (false);
		else
			input++;
	}
	while (*input)
	{
		if (!ft_isdigit(*input))
			return (false);
		input++;
	}
	return (true);
}

/*
	Exit from its current execution environment with the last command's exit status code.
	Argument is specified  by  the  unsigned  decimal integer n
	(which belongs to the range of LLONG_MIN - LLONG_MAX).

	- When argc > 1, it doesn't exit, status 1
	- if it's in a pipe, shell doesn't exit,
		doesn't print exit. Just changes exit status 🤷‍♀️
*/
int	cmd_exit(char **args)
{
	int	exit_stat;
	int	argc;
	int	nbr_range_error;

	nbr_range_error = 0;
	argc = arrlen(args);
	exit_stat = ft_atoll(*args, &nbr_range_error);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (argc == 0)
		exit_stat = set_and_get_exit_status(-1, false);
	else if (!is_numeric(*args) || nbr_range_error)
	{
		print_exit_arg_err(*args);
		// cleanup
		exit(2);
	}
	else if (argc > 1)
	{
		print_cmd_err("exit", "too many arguments");
		return (FAILURE);
	}
	// cleanup before exit?
	exit(exit_stat & 255);
}
