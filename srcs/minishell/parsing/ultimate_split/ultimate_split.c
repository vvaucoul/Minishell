/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 18:47:02 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/03 17:42:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*get_lst(char *str)
{
	t_list		*start;

	if (!(start = ft_lstnew(str)))
		return (NULL);
	if (lst_split(start, " ", 0))
		return (NULL);
	if (lst_split(start, "|", 1))
		return (NULL);
	if (lst_split(start, "<", 1))
		return (NULL);
	if (lst_split(start, ">", 1))
		return (NULL);
	start = del_empty(start);
	return (start);
}

char		**get_res(t_list *lst_split)
{
	char		**res;
	int			i;

	i = ft_lstsize(lst_split);
	if (!(res = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	res[i] = NULL;
	i = 0;
	while (1)
	{
		if (!(res[i] = ft_strdup(lst_split->content)))
			return (NULL);
		if (!lst_split->next)
			return (res);
		lst_split = lst_split->next;
		i++;
	}
	return (res);
}

void		get_cmd(char *str)
{
	int			i;
	int			quote;
	int			drift;

	quote = 0;
	drift = 0;
	i = 0;
	while (str[i + drift])
	{
		if ((str[i + drift] == '\'' && quote == 1)
			|| (str[i + drift] == '"' && quote == 2))
			quote = 0;
		else if (str[i + drift] == '\'' && quote == 0)
			quote = 1;
		else if (str[i + drift] == '"' && quote == 0)
			quote = 2;
		else
		{
			str[i] = str[i + drift];
			i++;
			continue;
		}
		drift++;
	}
	str[i] = '\0';
}

void		free_lst(t_list *lst)
{
	t_list		*tmp;

	while (lst->next)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
	free(lst->content);
	free(lst);
}

char		**ultimate_quotesplit(char *str)
{
	t_list		*lst_split;
	char		**res;
	int			i;

	if (!(lst_split = get_lst(str)))
		return (NULL);
	if (!(res = get_res(lst_split)))
		return (NULL);
	free_lst(lst_split);
	i = -1;
	while (++i < ft_tablen(res))
		get_cmd(res[i]);
	return (res);
}
