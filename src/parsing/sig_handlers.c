/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:42:32 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/07 23:08:40 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sighandler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", STDIN_FILENO);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
		printf("Quit: %d\n", signal);
	set_and_get_exit_status(128 + signal, true);
}

int	sig_handler_heredoc(void)
{
	if (g_signal == SIGINT)
		rl_done = 1;
	return (0);
}
