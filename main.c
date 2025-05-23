/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:41:07 by hvahib            #+#    #+#             */
/*   Updated: 2025/05/18 00:08:51 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

volatile int	g_signal;

int	main(int ac, char **av, char **envp)
{
	char		*cur_dir;
	int			fd_in;
	int			fd_out;
	t_env_pack	env_pack;

	(void)ac;
	(void)av;
	cur_dir = NULL;
	cur_dir = getcwd(NULL, 0); // get the current working directory
	if (!cur_dir)
		return (1);                  // handle error if getcwd fails
	fd_in = dup(STDIN_FILENO);       // duplicate stdin
	fd_out = dup(STDOUT_FILENO);     // duplicate stdout
	if (fd_in == -1 || fd_out == -1) // check for errors in dup
		return (free(cur_dir), 1);
	env_pack = init_env_pack(envp, cur_dir);
	minishell(env_pack);
	return (0);
}
