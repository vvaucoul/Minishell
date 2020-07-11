/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:15:20 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/11 22:42:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*epur_b_str(char *str)
{
	char *new_str;
	int i;
	int j;

	i = 0;
	j = 0;

	if (!str)
		return (NULL);
	if (!(new_str = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[i])
	{
		if (str[i] != 34 && str[i] != 39)
		{
			new_str[j] = str[i];
			++j;
		}
		++i;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

T_BOOL	tab_has_pipe(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (!(ft_strcmp(tab[i], "|")))
		return (TRUE);
		++i;
	}
	return (FALSE);
}

T_BOOL	tab_has_redirection(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (r_is_redirection(tab[i]))
		return (TRUE);
		++i;
	}
	return (FALSE);
}

int		tab_len(char **tab)
{
	int i;

	if (!(tab))
		return (-1);
	i = 0;
	while (tab[++i]);
	return (i);
}
