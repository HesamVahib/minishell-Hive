/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:41:23 by hvahib            #+#    #+#             */
/*   Updated: 2025/05/11 20:21:44 by hvahib           ###   ########.fr       */
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

void	minishell(t_env_pack env_pack)
{
	char	*line;
	char	**tokenz;
	t_cmd	*cmd_args;
	int		i;

	while (1)
	{
		if (change_mode(WAIT_FOR_COMMAND))
			clean_out_all(env_pack.sys_envlist, env_pack.mshell_env, NULL,
				NULL);
		line = readline(SHELL_PROMPT);
		if (!line)
			exit_preparation(env_pack);
		if (executable(line))
		{
			add_history(line);
			env_pack = export_std_fd(env_pack);
			tokenz = line_tokenized(line, env_pack.mshell_env);
			if (tokenz)
			{
				cmd_args = cmd_args_extractor(tokenz);
				print_cmd_temp(cmd_args);
				i = heredoc_processing(cmd_args);
			}
			else
			{
				init_cmd_list(cmd_args, 0);
				printf("something HAPPENED in tokenization\n");
			}
			printf("\n\nExecution...\n\n");
			// 🌟 execute_cmd
			if (cmd_args && cmd_args->argv)
				exec_cmd(cmd_args, env_pack.mshell_env);
			restore_std_fd(env_pack);
			// reset the the fd's to get back to the default one if something like | (pipe) had appled on std's
		}
		free(line);
	}
}
