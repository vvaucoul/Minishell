/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:15:20 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/22 16:39:33 by mle-faou         ###   ########.fr       */
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
		if ((str[i] != '"' && str[i] != '\'') || is_in_quotes(str, i))
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

T_BOOL	tab_has_pipe(char **tabl)
{
	int i;

	i = 0;
	while (tabl[i])
	{
		if (!(ft_strcmp(tabl[i], "|")))
		return (TRUE);
		++i;
	}
	return (FALSE);
}

T_BOOL	tab_has_redirection(char **tabl)
{
	int i;

	i = 0;
	while (tabl[i])
	{
		if (r_is_redirection(tabl[i]))
		return (TRUE);
		++i;
	}
	return (FALSE);
}

int		tab_len(char **tabl)
{
	int i;

	if (!(tabl))
		return (-1);
	i = 0;
	while (tabl[++i]);
	return (i);
}
