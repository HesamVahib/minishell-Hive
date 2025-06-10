/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:07:04 by michoi            #+#    #+#             */
/*   Updated: 2024/11/18 14:04:34 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*clear_lst(t_list *lst, void (*del)(void *))
{
	ft_lstclear(&lst, del);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*mapped;
	void	*f_output;

	new = 0;
	if (!f || !del)
		return (0);
	while (lst)
	{
		f_output = f(lst -> content);
		if (!f_output)
			return (clear_lst(new, del));
		mapped = ft_lstnew(f_output);
		if (!mapped)
		{
			del(f_output);
			return (clear_lst(new, del));
		}
		ft_lstadd_back(&new, mapped);
		lst = lst -> next;
	}
	return (new);
}
