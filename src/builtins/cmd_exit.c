<<<<<<< HEAD:builtins/cmd_exit.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:19:52 by michoi            #+#    #+#             */
/*   Updated: 2025/05/26 14:56:40 by hvahib           ###   ########.fr       */
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
	(which belongs to the range of LLONG_MIN - LLONG_MAX).
*/
// ☠️❓ if it's in a pipe, shell doesn't exit, doesn't print exit. Just changes exit status 🤷‍♀️

// If the current execution environment is a subshell environment,
// the shell shall exit from the subshell environment
// with the specified exit status and continue in the environment from which that subshell environment was invoked.
int	cmd_exit(char **args)
{
	int	exit_stat;
	int	argc;
	int	nbr_range_error;

	nbr_range_error = 0;
	// !! fix later. It should have the last command's exit code
	if (!args)
		exit_stat = 0;
	else
	{
		if (*args && !is_numeric(*args))
		{
			print_str_arg_err(*args);
			// cleanup
			exit(2);
		}
		argc = arrlen(args);
		if (is_numeric(*args) && argc > 1)
		{
			print_cmd_err("exit", "too many arguments");
			// doesn't exit, status 1
			return (FAILURE);
		}
		exit_stat = ft_atoll(*args, &nbr_range_error);
		if (nbr_range_error)
		{
			print_str_arg_err(*args);
			// cleanup
			exit(2);
		}
	}
	ft_putendl_fd("exit", STDOUT_FILENO);
	// cleanup before exit?
	exit(exit_stat & 255);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:19:52 by michoi            #+#    #+#             */
/*   Updated: 2025/06/09 22:54:21 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

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

static void	cleanup_exit(t_env *env, t_cmd *cmd)
{
	exit_run(env);
	free_cmd_list(cmd);
}

/*
	Exit from its current execution environment with the exit status.
	specified  by  the  unsigned  decimal integer n
	(which belongs to the range of LLONG_MIN - LLONG_MAX).
*/
int	cmd_exit(t_env *env, t_cmd *cmd)
{
	long long	exit_stat;
	int			nbr_range_error;
	char		**args;

	args = cmd->argv + 1;
	nbr_range_error = 0;
	if (!cmd->previous && !cmd->is_piped)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!args || !*args)
		exit_stat = set_and_get_exit_status(-1, false);
	else
	{
		exit_stat = ft_atoll(*args, &nbr_range_error);
		if ((*args && !is_numeric(*args)) || nbr_range_error)
		{
			print_cmd_err_with_arg("exit", *args, "numeric argument required");
			cleanup_exit(env, cmd);
			exit(2);
		}
		if (is_numeric(*args) && arrlen(args) > 1)
			return (print_cmd_err("exit", "too many arguments"), FAILURE);
	}
	cleanup_exit(env, cmd);
	exit(exit_stat & 255);
}
>>>>>>> 874a9b48f3199909f568ebc8744a2ebc01ae86ce:src/builtins/cmd_exit.c
