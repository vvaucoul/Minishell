/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 15:27:30 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/01 18:20:31 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char *echo_epur_str(char *str)
{
	char *new_str;
	int i;
	int j;

	i = 0;
	j = 0;

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
	return (new_str);
}

static int	find_first_arg(char **tab, T_BOOL has_argument)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (!(ft_strcmp(tab[i], "echo")))
			return (i + (has_argument ? 2 : 1));
		++i;
	}
	return (i);
}

int		b_echo(char **tab, T_BOOL has_argument)
{
	int i;

	if (!tab)
		return (-1);
	tab[0] = get_cmd_in_path(tab[0]);
	i = find_first_arg(tab, has_argument);
	if (!tab[i] && has_argument)
		return (0);
	while (tab[i])
	{
		ft_putstr_fd(echo_epur_str(tab[i]), 1);
		if (tab[i + 1])
		ft_putchar_fd(' ', 1);
		++i;
	}
	if (!has_argument)
	ft_putchar_fd('\n', 1);
	return (0);
}
