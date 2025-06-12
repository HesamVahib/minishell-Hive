/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:42:06 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 16:43:16 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	running_command(void)
{
	g_signal = 0;
	if (signal(SIGINT, &sighandler) == SIG_ERR)
		return (1);
	return (0);
}

static int	wait_for_command(void)
{
	g_signal = 0;
	if (signal(SIGINT, &sighandler) == SIG_ERR)
		return (1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (1);
	return (0);
}

int	change_mode(int mode)
{
	if ((mode == RUNNING_COMMAND) && (running_command()))
		return (1);
	else if ((mode == WAIT_FOR_COMMAND) && (wait_for_command()))
		return (1);
	return (0);
}
