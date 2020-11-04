/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_here.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 19:57:34 by mle-faou          #+#    #+#             */
/*   Updated: 2020/09/30 19:29:00 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstadd_here(t_list *lst, char *new_content, int to_free)
{
	t_list *new_node;

	if (!(new_node = ft_lstnew(new_content)))
		return (1);
	if (to_free)
		free(new_content);
	new_node->next = lst->next;
	lst->next = new_node;
	return (0);
}
