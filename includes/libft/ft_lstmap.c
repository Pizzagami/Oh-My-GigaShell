/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selgrabl <selgrabl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:30:48 by selgrabl          #+#    #+#             */
/*   Updated: 2019/10/20 13:50:22 by selgrabl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *list;
	t_list *tmp;

	list = NULL;
	if (lst && f)
	{
		if (!(list = ft_lstnew(f(lst->content))))
			return (NULL);
		tmp = list;
		while ((lst = lst->next))
		{
			if (!(tmp->next = ft_lstnew(lst->content)))
			{
				ft_lstclear(&list, del);
				return (NULL);
			}
			tmp = tmp->next;
		}
	}
	return (list);
}
