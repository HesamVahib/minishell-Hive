/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:19:52 by michoi            #+#    #+#             */
/*   Updated: 2025/04/16 14:14:04 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

static void	print_str_arg_err(char *arg)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
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
	Exit from its current execution environment with the exit status.
	specified  by  the  unsigned  decimal integer n
	(belongs to the range of LLONG_MIN - LLONG_MAX).
*/
// ❓ if it's in a pipe, shell doesn't exit, doesn't print exit.

// If the current execution environment is a subshell environment,
// the shell shall exit from the subshell environment
// with the specified exit status and continue in the environment from which that subshell environment was invoked.
int	cmd_exit(char **args)
{
	int	exit_stat;
	int	argc;
	int	nbr_range_error;

	nbr_range_error = 0;
	if (!args)
		exit_stat = 0;
	// !! fix later. It should have the last command's exit code
	else
	{
		if (!is_numeric(*args))
		{
			print_str_arg_err(*args);
			// cleanup
			exit_stat = 2;
			exit(exit_stat);
		}
		argc = arrlen(args);
		if (is_numeric(*args) && argc > 1)
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putendl_fd("too many arguments", STDERR_FILENO);
			// doesn't exit, status 1
			return (FAILURE);
		}
		exit_stat = ft_atoll(*args, &nbr_range_error);
		if (nbr_range_error)
		{
			print_str_arg_err(*args);
			// cleanup
			exit_stat = 2;
			exit(exit_stat);
		}
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	// cleanup before exit?
	exit(exit_stat & 255);
}
