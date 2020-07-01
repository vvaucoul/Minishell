/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:40:16 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/06/30 19:44:52 by vvaucoul         ###   ########.fr       */
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
	int i;

	i = 0;
	while (tab[i])
	{
		if (r_is_redirection(tab[i]))
		{
			tab[i] = NULL;
			return (tab);
		}
		++i;
	}
	return (tab);
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
