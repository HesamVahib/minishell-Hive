/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:19:52 by michoi            #+#    #+#             */
/*   Updated: 2025/04/14 22:17:01 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

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
	specified  by  the  unsigned  decimal integer n.
*/
void	exit(char **args)
{
	int exit_stat;
	int	argc;

	if (!args)
		exit_stat = 0; // !! fix later. It should have the last command's exit code
	else
	{
		if (!is_numeric(*args))
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			print_cmd_err_with_arg("exit", *args, "numeric argument required");
			exit_stat = 2;
			//cleanup
			exit(exit_stat);
		}
		argc = arrlen(args);
		if (is_numeric(*args) && argc > 1)
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putendl_fd("too many arguments", STDERR_FILENO);
			//doesn't exit
			return (FAILURE);
		}
		// long long ..
		exit_stat = ft_atoi(*args);
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	//cleanup before exit?
	exit(exit_stat & 255);

	// If the current execution environment is a subshell environment,
	// the shell shall exit from the subshell environment
	// with the specified exit status and continue in the environment from which that subshell environment was invoked.
}
