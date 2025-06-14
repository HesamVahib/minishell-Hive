/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:34:02 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 16:43:05 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_single_cmd(t_cmd *cmd, int k, int n_pipe, t_cmd *cmd_list)
{
	cmd->error = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->infile_fd = -1;
	cmd->outfile_fd = -1;
	cmd->heredoc_fd = -1;
	cmd->append = 0;
	cmd->is_heredoc = NULL;
	cmd->heredoc_limiters = NULL;
	cmd->argv = NULL;
	cmd->is_piped = 0;
	cmd->redirect_order = 0;
	if (k < n_pipe)
		cmd->next = &cmd_list[k + 1];
	else
		cmd->next = NULL;
	if (k > 0)
		cmd->previous = &cmd_list[k - 1];
	else
		cmd->previous = NULL;
}

void	init_cmd_list(t_cmd *cmd_list, int n_pipe)
{
	int	k;

	k = 0;
	if (!cmd_list)
		return ;
	while (k <= n_pipe)
	{
		init_single_cmd(&cmd_list[k], k, n_pipe, cmd_list);
		k++;
	}
}
