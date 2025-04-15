/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:24:15 by michoi            #+#    #+#             */
/*   Updated: 2025/04/15 15:16:35 by hvahib           ###   ########.fr       */
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

// ─── ⋆⋅☆⋅⋆ ── builtin commands ─── ⋆⋅☆⋅⋆ ──

// int		echo(char **args);
// int		pwd(void);
// int		env(t_env *env, char **args);
// void	cmd_exit(char **args);

// ─── ⋆⋅☆⋅⋆ ── utils ─── ⋆⋅☆⋅⋆ ──

void	print_cmd_err(char *cmd, char *msg);
void	print_cmd_err_with_arg(char *cmd, char *arg, char *msg);

#endif
