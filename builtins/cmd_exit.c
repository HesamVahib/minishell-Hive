/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:19:52 by michoi            #+#    #+#             */
/*   Updated: 2025/06/06 19:37:23 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

static void	print_str_arg_err(char *arg)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	print_cmd_err_with_arg("exit", arg, "numeric argument required");
}

static void	cleanup_exit(t_env *env, t_cmd *head)
{
	cleanup_env(env);
	free_cmd_list(head);
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
	(which belongs to the range of LLONG_MIN - LLONG_MAX).
*/
int	cmd_exit(t_env *env, t_cmd *cmd, t_cmd *head)
{
	long long	exit_stat;
	int			argc;
	int			nbr_range_error;
	char		**args;

	args = cmd->argv + 1;
	nbr_range_error = 0;
	if (!args || !*args)
		exit_stat = 0;
	else
	{
		exit_stat = ft_atoll(*args, &nbr_range_error);
		if ((*args && !is_numeric(*args)) || nbr_range_error)
		{
			print_str_arg_err(*args);
			cleanup_exit(env, head);
			exit(2);
		}
		argc = arrlen(args);
		if (is_numeric(*args) && argc > 1)
			return (print_cmd_err("exit", "too many arguments"), FAILURE);
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	cleanup_exit(env, head);
	exit(exit_stat);
}
