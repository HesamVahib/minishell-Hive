<<<<<<< HEAD:builtins/cmd_pwd.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:24:38 by michoi            #+#    #+#             */
/*   Updated: 2025/04/16 14:18:12 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

/**
	Print name of current/working directory.
	This function works without any options.
	@return
		SUCCESS - Operation completed successfully.

		FAILURE - Operation failed due to an error.
*/
int	cmd_pwd(void)
{
	char	buffer[PATH_MAX];

	if (!getcwd(buffer, PATH_MAX))
	{
		perror("pwd");
		return (FAILURE);
	}
	ft_putendl_fd(buffer, STDOUT_FILENO);
	return (SUCCESS);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:24:38 by michoi            #+#    #+#             */
/*   Updated: 2025/06/07 14:50:01 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

/**
	Print name of current/working directory.
	This function works without any options.
	@return
		SUCCESS - Operation completed successfully.

		FAILURE - Operation failed due to an error.
*/
int	cmd_pwd(void)
{
	char	buffer[PATH_MAX];

	if (!getcwd(buffer, PATH_MAX))
	{
		perror("pwd");
		return (FAILURE);
	}
	ft_putendl_fd(buffer, STDOUT_FILENO);
	return (SUCCESS);
}
>>>>>>> 874a9b48f3199909f568ebc8744a2ebc01ae86ce:src/builtins/cmd_pwd.c
