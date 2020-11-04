/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_split_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:29:53 by user42            #+#    #+#             */
/*   Updated: 2020/11/02 20:39:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Utils operator
*/

char			**operator_newtab(char **tabl)
{
	char **new_tab;

	if (!(new_tab = malloc(sizeof(char *) * ((ft_full_tablen(tabl) + 1)))))
		return (NULL);
	new_tab[0] = NULL;
	return (new_tab);
}

int				line_has_operator(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1])
		{
			if (str[i] == '&' && str[i + 1] == '&')
				return (1);
			else if (str[i] == '|' && str[i + 1] == '|')
				return (2);
		}
		++i;
	}
	return (0);
}

int				isinstr(char c, char *s)
{
	int i;

	i = 0;
	while (s[i])
		if (s[i++] == c)
			return (1);
	return (0);
}
