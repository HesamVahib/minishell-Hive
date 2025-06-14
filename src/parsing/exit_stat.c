/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_stat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 21:07:45 by michoi            #+#    #+#             */
/*   Updated: 2025/06/11 16:41:24 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_and_get_exit_status(int code, bool set)
{
	static int	stat_code = 0;

	if (set)
		stat_code = code;
	return (stat_code);
}
