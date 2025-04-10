/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:15:43 by michoi            #+#    #+#             */
/*   Updated: 2025/04/10 17:49:59 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	arrlen(void **arr)
{
	int len;

	if (!arr || !*arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

/**
	Change working directory.
	@param args: arguments
	@return
		SUCCESS - Operation completed successfully.

		FAILURE - Operation failed due to an error.
*/
int	cd(char **args)
{
	int	argc;

	argc = arrlen(args);
	if (argc > 1)
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		return (FAILURE);
	}
	if (!argc)
	{
		// going home
		chdir(".");
		return (SUCCESS);
	}
}
