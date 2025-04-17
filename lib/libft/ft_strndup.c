/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvahib <hvahib@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:47:40 by hvahib            #+#    #+#             */
/*   Updated: 2025/04/17 11:47:41 by hvahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *s, int n)
{
    char *dup;
    int i;

    dup = malloc(n + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (i < n)
    {
        dup[i] = s[i];
        i++;
    }
    dup[n] = '\0';
    return dup;
}