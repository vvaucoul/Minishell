/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_realloc_envp.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:44:55 by user42            #+#    #+#             */
/*   Updated: 2020/11/01 10:46:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			realloc_tab_set_values(char **new_tab, int line_add, char **tabl)
{
	int		i;
	int		j;

	i = 0;
	while (tabl[i])
	{
		if (!(new_tab[i] = ft_strdup(tabl[i])))
			return (FALSE);
		++i;
	}
	j = 0;
	while (j < line_add)
	{
		new_tab[i] = NULL;
		++i;
		++j;
	}
	new_tab[i] = NULL;
	return (TRUE);
}

char		**ft_realloc_tab(char **tabl, int col_add, int line_add, t_bool tf)
{
	char	**new_tab;

	if (!tabl)
		return (NULL);
	if (line_add <= 0 || col_add <= 0)
		return (tabl);
	if (!(new_tab = malloc(sizeof(char *) *
		(ft_full_tablen(tabl) + (col_add * line_add)))))
		return (NULL);
	if (!(realloc_tab_set_values(new_tab, line_add, tabl)))
		return (NULL);
	if (tf)
		ft_freetab(tabl);
	return (new_tab);
}
