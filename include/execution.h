/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:34:15 by michoi            #+#    #+#             */
/*   Updated: 2025/05/06 23:11:58 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "minishell.h"

typedef struct s_cmd t_cmd;
typedef struct s_env	t_env;

int	execute_cmd(t_cmd *cmd_args, t_env *env);

#endif
