/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:19:52 by michoi            #+#    #+#             */
/*   Updated: 2025/04/15 14:05:27 by hvahib           ###   ########.fr       */
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
void	cmd_exit(char **args)
{
	int exit_stat;

	if (!args)
		exit_stat = 0;
	else
	{
		if (!is_numeric(*args))
		{
			print_cmd_err_with_arg("exit", *args, "numeric argument required");
			//exit code 2
			return (FAILURE);
		}
		exit_stat = ft_atoi(*args);
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	//cleanup before exit?
	exit(exit_stat);

	// If the current execution environment is a subshell environment,
	// the shell shall exit from the subshell environment
	// with the specified exit status and continue in the environment from which that subshell environment was invoked.
}
