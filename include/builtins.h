/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:24:15 by michoi            #+#    #+#             */
/*   Updated: 2025/04/10 17:53:03 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// delete minishell lib later!
# include "./minishell.h"
# include <errno.h>
# include <linux/limits.h>
# include <stdbool.h>

# define CMD_ECHO "echo"
# define CMD_CD "cd"
# define CMD_PWD "pwd"
# define CMD_EXPORT "export"
# define CMD_UNSET "unset"
# define CMD_ENV "env"
# define CMD_EXIT "exit"

int	echo(char **args);
int	pwd(void);

#endif
