/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 21:19:52 by michoi            #+#    #+#             */
/*   Updated: 2025/04/06 21:31:44 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// delete includes after making a proper header!
#include <stdlib.h>

/*
	Exit from its current execution environment with the exit status.
	specified  by  the  unsigned  decimal integer n.
*/
void	exit(int exit_stat)
{
	exit(exit_stat);
	//

	// If the current execution environment is a subshell environment,
	// the shell shall exit from the subshell environment
	// with the specified exit status and continue in the environment from which that subshell environment was invoked.
}
