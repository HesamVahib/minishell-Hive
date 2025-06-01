/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_stat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 21:07:45 by michoi            #+#    #+#             */
/*   Updated: 2025/06/01 21:04:32 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

/**
 * When a cmd is executed, this function is called, and the exit status code is stored and returned.
 * @param code: The exit status code of the executed command.
 * @param set: determines whether to set or get the stat code.
 */
int	set_and_get_exit_status(int code, bool set)
{
	static int stat_code = 0;
	if (set)
		stat_code = code;
	// custom_export()
	return (stat_code);
}