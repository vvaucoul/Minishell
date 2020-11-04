/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_split_assign_tab.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:33:21 by user42            #+#    #+#             */
/*   Updated: 2020/11/02 20:37:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Append Tab
*/

char		**append_tab(char **tabl, char **new_tab)
{
	char	**result_tab;
	int		i;
	int		j;

	if (!(result_tab = malloc(sizeof(char *) * (ft_full_tablen(tabl) +
	ft_full_tablen(new_tab)))))
		return (NULL);
	i = 0;
	j = 0;
	while (tabl[i])
	{
		result_tab[i] = ft_strdup(tabl[i]);
		++i;
	}
	while (new_tab[j])
	{
		result_tab[i] = ft_strdup(new_tab[j]);
		++j;
		++i;
	}
	result_tab[i] = NULL;
	ft_freetab(tabl);
	ft_freetab(new_tab);
	return (result_tab);
}

/*
** Loop assign new tab
*/

char		**assign_op_tab(char **new_tab, char **tabl)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tabl[i])
	{
		if (line_has_operator(tabl[i]) > 0)
		{
			new_tab = append_tab(new_tab, split_operators(tabl[i]));
			j = ft_tablen(new_tab);
		}
		else
		{
			new_tab[j] = ft_strdup(tabl[i]);
			new_tab[j + 1] = NULL;
			++j;
		}
		++i;
	}
	return (new_tab);
}
