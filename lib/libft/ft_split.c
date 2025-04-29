/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:01:07 by michoi            #+#    #+#             */
/*   Updated: 2025/04/27 20:18:22 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if ((*s != c) && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

void	free_array(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

static char	*allocate_word(int start, int end, char const *s)
{
	char	*word;
	int		i;

	word = malloc(end - start + 1);
	if (!word)
		return (0);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = 0;
	return (word);
}

static int	add_words(char **arr, char const *s, char c)
{
	int	start;
	int	end;
	int	i;

	i = 0;
	start = 0;
	while (s[start])
	{
		if (s[start] != c)
		{
			end = start;
			while (s[end] != c && s[end])
				end++;
			arr[i] = allocate_word(start, end, s);
			if (!arr[i])
				return (0);
			start = end;
			i++;
		}
		else
			start++;
	}
	arr[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (0);
	result = malloc(sizeof(*result) * (count_words(s, c) + 1));
	if (!result)
		return (0);
	if (!add_words(result, s, c))
		free_array(&result);
	return (result);
}
