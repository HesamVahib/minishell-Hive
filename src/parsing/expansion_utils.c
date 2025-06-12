/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:39:52 by hvahib            #+#    #+#             */
/*   Updated: 2025/06/11 18:07:04 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*handle_normal_char(char *res, char *str, int *i)
{
	char	*new_res;
	
	new_res = append_char(res, str[*i]);
	*i = *i + 1;
	return (new_res);
}

static char	*handle_single_dollar(char *res, char *str, int *i, t_env *env)
{
	char	*var_key;
	char	*var_value;
	char	*new_res;

	var_key = extract_var_key(&str[*i + 1]);
	var_value = find_value_from_env(env, var_key);
	if (var_value)
		new_res = ft_strjoin(res, var_value);
	else
		new_res = ft_strjoin(res, "");
	*i = *i + ft_strlen(var_key) + 1;
	free(res);
	free(var_key);
	return (new_res);
}

static char	*handle_double_dollar(char *res, int *i)
{
	char	*pid_str;
	char	*new_res;

	pid_str = ft_strdup("$$");
	new_res = ft_strjoin(res, pid_str);
	free(res);
	free(pid_str);
	*i = *i + 2;
	return (new_res);
}

char	*process_dollars(char *token, t_env *env)
{
	char	*res;
	char	*new_str;
	char	*str;
	int		i;

	res = ft_strdup("");
	str = token;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			new_str = handle_single_dollar(res, str, &i, env);
		else if (str[i] == '$' && str[i + 1] && str[i + 1] == '$')
			new_str = handle_double_dollar(res, &i);
		else
			new_str = handle_normal_char(res, str, &i);
		if (!new_str)
			return (NULL);
		res = new_str;
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
