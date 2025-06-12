/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:15:43 by michoi            #+#    #+#             */
/*   Updated: 2025/06/11 16:44:19 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

static int	change_directory(char *path)
{
	if (chdir(path))
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror("chdir");
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	change_pwd_vars(t_env *env)
{
	char	*old_pwd;
	char	*old_pwd_cpy;
	char	*new_pwd;

	old_pwd = find_value_from_env(env, "PWD");
	if (!old_pwd)
		old_pwd_cpy = ft_strdup("");
	else
		old_pwd_cpy = ft_strdup(old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("cd: getcwd");
		return (free(old_pwd_cpy), free(new_pwd), FAILURE);
	}
	if (!custom_export(env, "OLDPWD", old_pwd_cpy))
		return (free(old_pwd_cpy), free(new_pwd), FAILURE);
	if (!custom_export(env, "PWD", new_pwd))
		return (free(old_pwd_cpy), free(new_pwd), FAILURE);
	return (free(old_pwd_cpy), free(new_pwd), SUCCESS);
}

static int	go_home_dir(t_env *env)
{
	char	*home_dir;

	home_dir = find_value_from_env(env, "HOME");
	if (!home_dir)
	{
		print_cmd_err("cd", "HOME not set");
		return (FAILURE);
	}
	if (change_directory(home_dir))
		return (FAILURE);
	if (change_pwd_vars(env))
		return (FAILURE);
	return (SUCCESS);
}

/**
 * 1. when the path doesn't exist
 * 2. when it's not a directory
 * 3. permission denied
 */
static bool	is_valid_path(char *path)
{
	struct stat	sb;

	if (stat(path, &sb))
	{
		print_cmd_err_with_arg("cd", path, strerror(ENOENT));
		return (false);
	}
	if (!S_ISDIR(sb.st_mode))
	{
		print_cmd_err_with_arg("cd", path, strerror(ENOTDIR));
		return (false);
	}
	if (access(path, X_OK))
	{
		print_cmd_err_with_arg("cd", path, strerror(EACCES));
		return (false);
	}
	return (true);
}

/**
	Change working directory.
	@param env: enviroment variables
	@param args: passed arguments, which contains target directory
	@return
		SUCCESS - Operation completed successfully.

		FAILURE - Operation failed due to an error.
*/
int	cmd_cd(t_env *env, char **args)
{
	int	argc;

	argc = arrlen(args);
	if (argc > 1)
	{
		print_cmd_err("cd", "too many arguments");
		return (FAILURE);
	}
	if (!argc)
	{
		if (go_home_dir(env))
			return (FAILURE);
		return (SUCCESS);
	}
	if (!is_valid_path(*args))
		return (FAILURE);
	else
	{
		if (change_directory(*args))
			return (FAILURE);
		if (change_pwd_vars(env))
			return (FAILURE);
	}
	return (SUCCESS);
}
