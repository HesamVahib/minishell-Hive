/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 21:39:53 by michoi            #+#    #+#             */
/*   Updated: 2025/04/09 13:44:20 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

/**
 * Check if a string is valid -n flag.
 *
 * Check if '-' char exists in the first position,
 * followed by at least one 'n'.
 * @param s: the string to be parsed.
 * @return
 * 	true - the string is a valid flag.
 *
 * 	false - the string is not a valid flag.
 */
bool	is_valid_n_flag(char *s)
{
	int	i;

	if (!s || *s)
		return (false);
	if (s[0] != '-')
		return (false);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/**
	Display the string(s) to standard output.
	@param str: the string to be displayed.
	@param option: option for the command. takes only -n
					(-n: do not output the trailing newline.)
	@return
		SUCCESS - Operation completed successfully.

		FAILURE - Operation failed due to an error.
*/
int	echo(char **args)
{
	int	i;
	int	suppress_newline;

	i = 0;
	suppress_newline = 0;
	while (args && args[i] && is_valid_n_flag(args[i]))
	{
		suppress_newline = 1;
		i++;
	}
	while (args && args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!suppress_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS);
}
