<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:24:15 by michoi            #+#    #+#             */
/*   Updated: 2025/05/25 01:25:37 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <errno.h>
# include <linux/limits.h>
# include <sys/stat.h>

# define CMD_ECHO "echo"
# define CMD_CD "cd"
# define CMD_PWD "pwd"
# define CMD_EXPORT "export"
# define CMD_UNSET "unset"
# define CMD_ENV "env"
# define CMD_EXIT "exit"

typedef struct s_env	t_env;

int						exec_builtin(t_env *env, char *cmd, char **args);

// ─── ⋆⋅☆⋅⋆ ── builtin commands ─── ⋆⋅☆⋅⋆ ──

int						cmd_cd(t_env *env, char **args);
int						cmd_echo(char **args);
int						cmd_env(t_env *env, char **args);
int						cmd_exit(char **args);
int						cmd_export(t_env *env, char **args);
int						cmd_pwd(void);
int						cmd_unset(t_env **env, char **args);

// ─── ⋆⋅☆⋅⋆ ── utils ─── ⋆⋅☆⋅⋆ ──

void					print_basic_error(char *cmd, char *msg);
void					print_cmd_err(char *cmd, char *msg);
void					print_cmd_err_with_arg(char *cmd, char *arg, char *msg);

#endif
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:24:15 by michoi            #+#    #+#             */
/*   Updated: 2025/06/09 19:39:40 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <errno.h>
# include <linux/limits.h>
# include <sys/stat.h>

# define CMD_ECHO "echo"
# define CMD_CD "cd"
# define CMD_PWD "pwd"
# define CMD_EXPORT "export"
# define CMD_UNSET "unset"
# define CMD_ENV "env"
# define CMD_EXIT "exit"

typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;

int						exec_builtin(t_env *env, t_cmd *cmd_arg);

// ─── ⋆⋅☆⋅⋆ ── builtin commands ─── ⋆⋅☆⋅⋆ ──

int						cmd_cd(t_env *env, char **args);
int						cmd_echo(char **args);
int						cmd_env(t_env *env, char **args);
int						cmd_exit(t_env *env, t_cmd *cmd);
int						cmd_export(t_env *env, char **args);
int						cmd_pwd(void);
int						cmd_unset(t_env **env, char **args);

// ─── ⋆⋅☆⋅⋆ ── utils ─── ⋆⋅☆⋅⋆ ──

void					print_basic_error(char *cmd, char *msg);
void					print_cmd_err(char *cmd, char *msg);
void					print_cmd_err_with_arg(char *cmd, char *arg, char *msg);

#endif
>>>>>>> 874a9b48f3199909f568ebc8744a2ebc01ae86ce
