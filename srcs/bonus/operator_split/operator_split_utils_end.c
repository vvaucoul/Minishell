/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_split_utils_end.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:32:39 by user42            #+#    #+#             */
/*   Updated: 2020/11/02 20:40:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** operator struct
*/

void		reset_mns_operators(t_mns *mns)
{
	int i;

	i = 0;
	while (i < MAX_CHAR_IN_PROMPT)
	{
		mns->operator.operator[i] = 0;
		++i;
	}
	mns->operator.result_cmd = 0;
	mns->operator.assign_operator = 0;
}

int			assign_operators(t_mns *mns, char **new_tab)
{
	int i;

	i = 0;
	while (new_tab[i])
	{
		if (!(ft_strcmp(new_tab[i], ";")))
			mns->operator.operator[mns->operator.assign_operator] = 1;
		if (!(ft_strcmp(new_tab[i], "&&")))
			mns->operator.operator[mns->operator.assign_operator] = 2;
		if (!(ft_strcmp(new_tab[i], "||")))
			mns->operator.operator[mns->operator.assign_operator] = 3;
		if (mns->operator.operator[mns->operator.assign_operator])
			++mns->operator.assign_operator;
		++i;
	}
	return (0);
}

char		**clean_operatortab(char **tabl)
{
	char	**new_tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new_tab = malloc(sizeof(char *) * (ft_full_tablen(tabl) + 1))))
		return (NULL);
	while (tabl[i])
	{
		if ((ft_strcmp(tabl[i], ";")) && (ft_strcmp(tabl[i], "&&")) &&
		(ft_strcmp(tabl[i], "||")))
		{
			if (!(new_tab[j] = ft_strdup(tabl[i])))
				return (NULL);
			++j;
		}
		++i;
	}
	new_tab[j] = NULL;
	ft_freetab(tabl);
	return (new_tab);
}
