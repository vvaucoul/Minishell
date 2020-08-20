/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:14:45 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/11 11:16:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char **sort_tab(char **tabl, int size, int i)
{
	int si;

	si = 0;
	tabl[i] = NULL;
	++i;
	while (si < size)
	{
		tabl[si] = tabl[si + 1];
		++si;
	}
	tabl[si] = NULL;
	return (tabl);
}

char	**remove_builtin_in_tab(char **tabl)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tabl[j++]);
	--j;
	while (tabl[i])
	{
		if (b_isvalid(tabl[i]))
			return (sort_tab(tabl, j, i));
		++i;
	}
	return (tabl);
}
