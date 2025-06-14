/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/05/08 12:41:23 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 20:58:39 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static int	executable(char *line)
{
	int i;

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
	t_cmd *head;
	t_cmd *current;
	t_cmd *next;

	head = find_head(cmd_args);
	current = head;
	while (current)
	{
		next = current->next;
		if (current->argv)
			free_array(&current->argv);
		free(current->infile);
		free(current->outfile);
		free(current->is_heredoc);
		if (current->heredoc_limiters)
			free_array(&current->heredoc_limiters);
		if (current->infile_fd >= 0)
			close(current->infile_fd);
		if (current->outfile_fd >= 0)
			close(current->outfile_fd);
		if (current->heredoc_fd >= 0)
			close(current->heredoc_fd);
		current = next;
	}
	free(head);
}

void	error_checking(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->error == 2)
		{
			print_cmd_err(cmd->infile, strerror(errno));
			set_and_get_exit_status(1, true);
		}
		if (cmd->error == 1)
		{
			print_cmd_err(cmd->outfile, strerror(errno));
			set_and_get_exit_status(1, true);
		}
		cmd = cmd->next;
	}
}

static void	process_command_line(char *line, t_env_pack *env_pack)
{
	char **tokenz;
	t_cmd *cmd_args;
	int argv_i;

	cmd_args = NULL;
	tokenz = NULL;
	add_history(line);
	*env_pack = export_std_fd(*env_pack);
	tokenz = line_tokenized(line, env_pack->mshell_env);
	if (tokenz)
	{
		cmd_args = cmd_args_extractor(tokenz);
		free_array(&tokenz);
		// print_cmd_temp(cmd_args);
		heredoc_processing(cmd_args);
		error_checking(cmd_args);
		free(tokenz);
	}
	else
		printf("something HAPPENED in tokenization\n");
	argv_i = check_valid_argv(cmd_args->argv);
	if (cmd_args && cmd_args->argv && argv_i < arrlen(cmd_args->argv))
		execution(cmd_args, env_pack);
	free_array(&tokenz);
	if (cmd_args)
		free_cmd_list(cmd_args);
	restore_std_fd(*env_pack);
}

void	minishell(t_env_pack env_pack)
{
	char *line;

	while (1)
	{
		if (change_mode(WAIT_FOR_COMMAND))
			clean_out_all(env_pack.sys_envlist, env_pack.mshell_env, NULL,
				NULL);
		line = readline(SHELL_PROMPT);
		if (!line)
		{
			exit_preparation(env_pack);
			exit(0);
		}
		if (executable(line))
			process_command_line(line, &env_pack);
		free(line);
	}
}
