/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:34:15 by michoi            #+#    #+#             */
/*   Updated: 2025/05/09 19:14:59 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <sys/wait.h>

typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;

typedef struct s_child_process
{
	int					file;
	char				*path;
	char				**args;
}						t_cp;

int						exec_cmd(t_cmd *cmd_args, t_env *env);

#endif
