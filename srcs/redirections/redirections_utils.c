/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:40:16 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/08 16:29:23 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

T_BOOL	r_is_redirection(char *str)
{
	if (!(ft_strcmp(str, ">")))
	return (TRUE);
	else if (!(ft_strcmp(str, ">>")))
	return (TRUE);
	else if (!(ft_strcmp(str, "<")))
	return (TRUE);
	return (FALSE);
}

int		r_get_redirection_pos(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (r_is_redirection(tab[i]))
		return (i);
		++i;
	}
	return (FALSE);
}

char **r_get_tab_without_redirection(char **tab)
{
	char **n_tab;
	int i;
	int j;

	i = 0;
	j = 0;
	n_tab = tab;
	while (tab[i])
	{
		if (r_is_redirection(tab[i]))
			++i;
		else
			n_tab[j] = tab[i];
		++i;
		++j;
	}
	n_tab[j] = NULL;
	return (n_tab);
}

char **r_get_tab_without_pipe(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "|"))
		{
			tab[i] = NULL;
			return (tab);
		}
		++i;
	}
	return (tab);
}
