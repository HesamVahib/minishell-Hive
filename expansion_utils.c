/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:52 by hvahib            #+#    #+#             */
/*   Updated: 2025/05/30 19:36:41 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static char	*handle_normal_char(char *res, char *str, int *i)
{
	printf("i am here\n");
	res = append_char(res, str[*i]);
	*i = *i + 1;
	return (res);
}

static char	*handle_single_dollar(char *res, char *str, int *i, t_env *env)
{
	char	*var_key;
	char	*var_value;

	var_key = extract_var_key(&str[*i + 1]);
	var_value = find_value_from_env(env, var_key);
	if (var_value)
		res = ft_strjoin(res, var_value);
	else
		res = ft_strjoin(res, "");
	*i = *i + ft_strlen(var_key) + 1;
	free(var_key);
	return (res);
}

static char	*handle_double_dollar(char *res, int *i)
{
	char	*pid_str;

	pid_str = ft_itoa(getpid());
	res = ft_strjoin(res, pid_str);
	free(pid_str);
	*i = *i + 2;
	return (res);
}

char	*process_dollars(char *token, t_env *env)
{
	char	*res;
	char	*str;
	int		i;

	res = ft_strdup("");
	str = token;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			res = handle_single_dollar(res, str, &i, env);
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '$')
			res = handle_double_dollar(res, &i);
		else
			res = handle_normal_char(res, str, &i);
	}
	return (res);
}

char	**surplus_dollar_remover(char **cmd_line) // echo "$$$'HOME'"
{
	int		i;
	char	**temp;
	char	**temp_split;

	temp = cmd_line;
	temp_split = NULL;
	i = 0;
	while (temp[i])
	{
		if ((temp[i][0] == '\\') || (temp[i][0] == '\''
				&& temp[i][ft_strlen(temp[i]) - 1] == '\''))
		{
			i++;
			continue ;
		}
		if (temp[i][0] != '\"' && (temp[i][0] != '$' && !temp[i][1]))
		{
			temp_split = ft_split(temp[i], '$');
			free(temp[i]);
			temp[i] = stitch_strings(temp_split);
			free(temp_split);
		}
		i++;
	}
	return (temp);
}
