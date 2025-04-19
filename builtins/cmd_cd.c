/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:15:43 by michoi            #+#    #+#             */
/*   Updated: 2025/04/19 21:45:08 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

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

static bool	is_valid_path(char *path)
{
	struct stat	sb;

	if (stat(path, &sb))
	{
		// doesn't exist
		print_cmd_err_with_arg("cd", path, strerror(ENOENT));
		return (false); // exit status 1
	}
	if (!S_ISDIR(sb.st_mode))
	{
		// not a dir
		print_cmd_err_with_arg("cd", path, strerror(ENOTDIR));
		return (false); // exit status 1
	}
	if (sb.st_mode == no permission)
	{
		print_cmd_err_with_arg("cd", path, strerror(EACCES));
		return (false); // exit status 1
	}
	return (true);
}

/**
	Change working directory.
	@param args: passed arguments, which contains target directory
	@param env: enviroment variables
	@return
		SUCCESS - Operation completed successfully.

		FAILURE - Operation failed due to an error.
*/
int	cmd_cd(t_env **env, char **args)
{
	int			argc;
	char		*home_dir;
	int			chdir_res;
	char		*temp_dir;

	argc = arrlen(args);
	if (argc > 1)
	{
		print_cmd_err("cd", "too many arguments");
		return (FAILURE);
	}
	if (!argc)
	{
		home_dir = find_value_from_env(*env, "HOME");
		if (!home_dir)
		{
			print_cmd_err("cd", "HOME not set");
			return (FAILURE);
		}
		if (change_directory(home_dir))
			return (FAILURE);
		// change PWD and OLDPWD vars
		return (SUCCESS);
	}
	if (!is_valid_path(*args))
		return (FAILURE);
	else
	{
		if (change_directory(*args))
			return (FAILURE);
		// change PWD and OLDPWD vars
	}
	return (SUCCESS);
}

// ☠️ edge cases
// when parent dir is removed. What to do?
// rm-rf-> cd . or ..: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
// and then add . or .. (dir/. or dir/..)
// and the if .. is passe again, it goes to home.
