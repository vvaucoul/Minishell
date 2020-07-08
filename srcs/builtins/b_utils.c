/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:14:45 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/02 16:24:48 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char **sort_tab(char **tab, int size, int i)
{
	int si;

	si = 0;
	tab[i] = NULL;
	++i;
	while (si < size)
	{
		tab[si] = tab[si + 1];
		++si;
	}
	tab[si] = NULL;
	return (tab);
}

char	**remove_builtin_in_tab(char **tab)
{
	int i;
	int j;

	i = 0;
	while (tab[j++]);
	--j;
	while (tab[i])
	{
		if (b_isvalid(tab[i]))
		return (sort_tab(tab, j, i));
		++i;
	}
	return (tab);
}
