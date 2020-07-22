/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:49:30 by mle-faou          #+#    #+#             */
/*   Updated: 2019/11/08 11:03:51 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *))
{
	t_list	*new_list;
	t_list	*current_list;

	if (!lst)
		return (NULL);
	current_list = ft_lstnew(f(lst->content));
	new_list = current_list;
	while (lst->next != NULL)
	{
		lst = lst->next;
		current_list->next = ft_lstnew(f(lst->content));
		current_list = current_list->next;
	}
	return (new_list);
}
