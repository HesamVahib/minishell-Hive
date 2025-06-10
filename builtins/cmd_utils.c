/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:26:19 by michoi            #+#    #+#             */
/*   Updated: 2025/05/13 16:23:37 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

/**
 * Print an error message with a command name to standard error in the basic form.
 * @param cmd: command name
 * @param msg: error message
 */
void	print_basic_error(char *cmd, char *msg)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

/**
 * Print an error message with a command name to standard error.
 * @param cmd: command name
 * @param msg: error message
 */
void	print_cmd_err(char *cmd, char *msg)
{
	ft_putstr_fd("(what the)shell: ", STDERR_FILENO);
	print_basic_error(cmd, msg);
}

/**
 * Print an error message with a command name and its argument to standard error.
 * @param cmd: command name
 * @param arg: argument name
 * @param msg: error message
 */
void	print_cmd_err_with_arg(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("(what the)shell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	print_basic_error(arg, msg);
}
