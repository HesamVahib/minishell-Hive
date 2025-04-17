/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:24:15 by michoi            #+#    #+#             */
/*   Updated: 2025/04/16 14:24:07 by michoi           ###   ########.fr       */
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

typedef struct s_env	t_env;

// ─── ⋆⋅☆⋅⋆ ── builtin commands ─── ⋆⋅☆⋅⋆ ──

int						cmd_cd(char **args, t_env *env);
int						cmd_echo(char **args);
int						cmd_env(t_env *env, char **args);
void					cmd_exit(char **args);
int						cmd_pwd(void);

// ─── ⋆⋅☆⋅⋆ ── utils ─── ⋆⋅☆⋅⋆ ──

void					print_cmd_err(char *cmd, char *msg);
void					print_cmd_err_with_arg(char *cmd, char *arg, char *msg);

#endif
