/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:15:43 by michoi            #+#    #+#             */
/*   Updated: 2025/04/09 14:54:41 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

/**
	Change the working directory.
	@param dir: the target directory.
	@return
		SUCCESS - Operation completed successfully.

		FAILURE - Operation failed due to an error.
*/
int	cd(char *dir)
{
	if (!dir)
	{
		// going home
		return (SUCCESS);
	}
}
