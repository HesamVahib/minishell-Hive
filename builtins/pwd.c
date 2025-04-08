/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:24:38 by michoi            #+#    #+#             */
/*   Updated: 2025/04/08 15:20:08 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// delete includes after making a proper header!
#include <linux/limits.h>
#include <stdio.h>
#include <unistd.h>

/**
	Print name of current/working directory.
	This function works without any options.
	@return
		0 - Operation completed successfully.

		1 - Operation failed due to an error.
*/
int	pwd(void)
{
	char	buffer[PATH_MAX];

	if (!getcwd(buffer, PATH_MAX))
	{
		perror("pwd");
		return (1);
	}

	// change it to smth else later?
	printf("%s\n", buffer);
	return (0);
}
