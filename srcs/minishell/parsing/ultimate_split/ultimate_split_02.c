/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_split_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 18:47:02 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/03 17:42:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			lst_cut(t_list **lst, char *to_cut, int keep, int i)
{
	int			size;
	char		*tmp;

	size = 1;
	if (ft_strstartswith((*lst)->content + i, "<<", 0, 0)
		|| ft_strstartswith((*lst)->content + i, ">>", 0, 0))
		size = 2;
	if (!(tmp = ft_strdup((*lst)->content)))
		return (1);
	if (!((*lst)->content = ft_strchangelen((*lst)->content, i)))
		return (1);
	if (keep)
	{
		if (size == 1)
			if (ft_lstadd_here(*lst, to_cut, 0))
				return (1);
		if (size == 2)
			if (ft_lstadd_here(*lst, ft_strjoin(to_cut, to_cut), 1))
				return (1);
		*lst = (*lst)->next;
	}
	if (ft_lstadd_here(*lst, ft_strdup(tmp + i + size), 1))
		return (1);
	free(tmp);
	return (0);
}

int			lst_split(t_list *lst, char *to_cut, int keep)
{
	int			i;

	while (1)
	{
		i = 0;
		while (((char*)lst->content)[i])
		{
			if (ft_strstartswith(lst->content + i, to_cut, 0, 0)
				&& !is_in_quotes(lst->content, i))
			{
				if (lst_cut(&lst, to_cut, keep, i))
					return (1);
				break ;
			}
			i++;
		}
		if (!lst->next)
			return (0);
		lst = lst->next;
	}
	return (0);
}

t_list		*del_empty(t_list *lst)
{
	t_list		*tmp;
	t_list		*inc;

	while (((char*)lst->content)[0] == '\0' && lst->next)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
	inc = lst;
	while (inc->next)
	{
		if (((char*)inc->next->content)[0] == '\0')
		{
			tmp = inc->next;
			inc->next = inc->next->next;
			free(tmp->content);
			free(tmp);
		}
		else
			inc = inc->next;
	}
	return (lst);
}
