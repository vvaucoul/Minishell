/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:59:00 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 19:59:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool		ft_stris_digit(char *str)
{
	int i;

	if (!(str))
		return (FALSE);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		++i;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

int			ft_full_tablen(char **tabl)
{
	int i;
	int j;
	int mj;

	i = 0;
	j = 0;
	mj = 0;
	while (tabl[i])
	{
		while (tabl[i][j])
			++j;
		if (j > mj)
			mj = j;
		j = 0;
		++i;
	}
	return (i * mj);
}

void		ft_init_to_null(void *str1, void *str2, void *str3, void *str4)
{
	if (str1)
		ft_bzero(str1, sizeof(char *));
	if (str2)
		ft_bzero(str2, sizeof(char *));
	if (str3)
		ft_bzero(str3, sizeof(char *));
	if (str4)
		ft_bzero(str4, sizeof(char *));
}

/*
** Check if only char are in this str
*/

t_bool		ft_is_in_range(char *str, int min, int max)
{
	int i;

	i = 0;
	printf("[%s] is between [%c] [%c]\n", str, min, max);
	while (str[i])
	{
		if (str[i] >= min && str[i] <= max)
			++i;
		else
			return (FALSE);
	}
	return (TRUE);
}
