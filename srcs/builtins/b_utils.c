/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:14:45 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 19:48:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**remove_builtin_in_tab(char **tabl)
{
	char	**new_tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new_tab = malloc(sizeof(char *) * ft_full_tablen(tabl))))
		return (NULL);
	while (tabl[i])
	{
		if (!(b_isvalid(tabl[i])))
		{
			if (!(new_tab[j] = ft_strdup(tabl[i])))
				return (NULL);
			++j;
		}
		++i;
	}
	new_tab[j] = NULL;
	return (new_tab);
}
