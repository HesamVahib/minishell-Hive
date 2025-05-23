/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_temp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:42:14 by hvahib            #+#    #+#             */
/*   Updated: 2025/05/23 15:18:04 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	print_cmd_temp(t_cmd *cmd_args)
{
	int i = 0;
	printf("in printing temp funtion\n");

	while (cmd_args != NULL)
	{
		printf("=== Command %d ===\n", i);
		if (cmd_args->error)
			printf("Error Happening\n");
		if (cmd_args->argv)
		{
			for (int j = 0; cmd_args->argv[j]; j++)
				printf("'%s' ", cmd_args->argv[j]);
			printf("\n");
		}
		if (cmd_args->infile)
			printf("infile1: '%s'\n", cmd_args->infile);
		if (cmd_args->outfile)
			printf("outfile: '%s' (append: %d)\n", cmd_args->outfile,
				cmd_args->append);
		if (cmd_args->is_heredoc)
			printf("heredoc limiter: '%s'\n", cmd_args->is_heredoc);
		if (cmd_args->is_heredoc)
		{
			for (int j = 0; cmd_args->heredoc_limiters[j]; j++)
				printf("'%s' ", cmd_args->heredoc_limiters[j]);
			printf("\n");
		}
		printf("is_piped: %d\n", cmd_args->is_piped);

		cmd_args = cmd_args->next;
		i++;
	}
}