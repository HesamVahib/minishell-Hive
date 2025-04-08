/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:23:39 by michoi            #+#    #+#             */
/*   Updated: 2024/11/15 20:12:45 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_node;

	if (lst && del)
	{
		while (*lst)
		{
			next_node = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = next_node;
		}
		lst = 0;
	}
}
