/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:15:43 by michoi            #+#    #+#             */
/*   Updated: 2025/04/12 18:25:56 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	print_cmd_err(char *cmd, char *msg)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

int	change_directory(char *path)
{
	if (chdir(path))
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror("chdir");
		return (FAILURE);
	}
	return (SUCCESS);
}

/**
	Change working directory.
	@param args: arguments
	@return
		SUCCESS - Operation completed successfully.

		FAILURE - Operation failed due to an error.
*/
int	cd(char **args, t_env *env)
{
	int		argc;
	char	*home_dir;
	int		chdir_res;

	argc = arrlen(args);
	if (argc > 1)
	{
		print_cmd_err("cd", "too many arguments");
		return (FAILURE);
	}
	// going home
	if (!argc)
	{
		home_dir = find_value_from_env(env, "HOME");
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
	if (access(*args, F_OK | X_OK))
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(*args);
		// exit status 1
		return (FAILURE);
	}
	else
	{
		if (change_directory(*args))
			return (FAILURE);
		// change PWD and OLDPWD vars
		return (SUCCESS);
	}
}

// ☠️ edge cases
// when parent dir is removed. What to do?
// rm -rf-> cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
