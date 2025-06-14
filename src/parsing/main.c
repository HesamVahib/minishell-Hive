/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:41:07 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 16:43:13 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_signal;

int	main(int ac, char **av, char **envp)
{
	char		*cur_dir;
	t_env_pack	env_pack;

	(void)ac;
	(void)av;
	cur_dir = NULL;
	cur_dir = getcwd(NULL, 0);
	if (!cur_dir)
		return (1);
	env_pack = init_env_pack(envp, cur_dir);
	minishell(env_pack);
	return (0);
}
