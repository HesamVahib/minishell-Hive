/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:41:23 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/01 23:56:01 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static int	executable(char *line)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (1);
		i++;
	}
	return (0);
}

void	free_cmd_list(t_cmd *cmd_args)
{
	t_cmd *tmp;

	while (cmd_args)
	{
		tmp = cmd_args->next;
		if (cmd_args->argv)
			free_array(&cmd_args->argv);
		free(cmd_args->infile);
		free(cmd_args->outfile);
		free(cmd_args->is_heredoc);
		free_array(&cmd_args->heredoc_limiters);
		cmd_args = tmp;
	}
}

void error_checking(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->error == 2) // it means no such file or directory
			print_cmd_err(cmd->infile, strerror(2));
		if (cmd->error == 1) // it means no such file or directory
			print_cmd_err(cmd->outfile, strerror(2));

		cmd = cmd->next;
	}
}

void	minishell(t_env_pack env_pack)
{
	char	*line;
	char	**tokenz;
	t_cmd	*cmd_args;

	while (1)
	{
		cmd_args = NULL;
		if (change_mode(WAIT_FOR_COMMAND))
			clean_out_all(env_pack.sys_envlist, env_pack.mshell_env, NULL,
				NULL);
		line = readline(SHELL_PROMPT);
		if (!line)
		{
			free(line);
			exit_preparation(env_pack);
		}
		tokenz = NULL;
		if (executable(line))
		{
			add_history(line);
			env_pack = export_std_fd(env_pack);
			tokenz = line_tokenized(line, env_pack.mshell_env);
			if (tokenz)
			{
				cmd_args = cmd_args_extractor(tokenz);
				print_cmd_temp(cmd_args);
				heredoc_processing(cmd_args);
				error_checking(cmd_args);
			}
			else
				printf("something HAPPENED in tokenization\n");
			if (cmd_args && cmd_args->argv && *(cmd_args->argv))
				execution(cmd_args, env_pack.mshell_env);
			// free_cmd_list(cmd_args);
			restore_std_fd(env_pack);
			// reset the the fd's to get back to the default one if something like | (pipe) had appled on std's
			printf("exit stat: %d\n", set_and_get_exit_status(-1, false));
		}
		free(line);
	}
}
