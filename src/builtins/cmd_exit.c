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
	cleanup_env(env);
	exit(exit_stat & 255);
}
