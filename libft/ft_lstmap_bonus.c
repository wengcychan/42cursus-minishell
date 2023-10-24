/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchan <wchan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:54:05 by wchan             #+#    #+#             */
/*   Updated: 2023/03/24 15:20:14 by wchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*current_new;

	if (!lst || !f || !del)
		return (NULL);
	res = NULL;
	while (lst)
	{
		current_new = ft_lstnew(f(lst->content));
		if (!current_new)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		ft_lstadd_back(&res, current_new);
		lst = lst->next;
	}
	return (res);
}
