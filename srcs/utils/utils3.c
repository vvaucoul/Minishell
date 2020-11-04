/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 10:21:00 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 16:49:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**move_table(char **tabl, int i)
{
	int tab_len;

	tab_len = -1;
	while (tabl[tab_len])
		++tab_len;
	while (tabl[tab_len] && tab_len > i)
	{
		tabl[tab_len] = tabl[tab_len - 1];
		--tab_len;
	}
	tabl[tab_len + 1] = NULL;
	return (tabl);
}

char			**add_default_flag(char **tabl)
{
	int i;

	i = 0;
	while (tabl[i])
	{
		if (!(ft_strcmp(tabl[i], "ls")) || !(ft_strcmp(tabl[i], "grep")))
		{
			tabl = move_table(tabl, i);
			tabl[i + 1] = ft_strdup("--color");
		}
		++i;
	}
	return (tabl);
}

int				ft_intlen(unsigned long long int nb)
{
	int count;

	count = 0;
	while (nb > 9)
	{
		nb /= 10;
		++count;
	}
	return (count);
}
