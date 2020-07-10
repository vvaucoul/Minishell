/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 15:27:30 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/10 19:55:35 by root             ###   ########.fr       */
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

static	T_BOOL	cmd_has_argument(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		if (!(ft_strcmp(tab[i], "-n")) && (!(ft_strcmp(tab[i - 1], "echo"))) &&
		i == 1)
		return (TRUE);
		++i;
	}
	return (FALSE);
}

int		b_echo(char **tab)
{
	T_BOOL	has_argument;
	char	*epured_str;
	int i;

	if (!tab)
		return (0);
	has_argument = cmd_has_argument(tab);
	i = find_first_arg(tab, has_argument);
	if (!tab[i] && has_argument)
		return (0);
	while (tab[i])
	{
		if (!(epured_str = echo_epur_str(tab[i])))
			return (-1);
		ft_putstr_fd(epured_str, 1);
		free(epured_str);
		if (tab[i + 1])
			ft_putchar_fd(' ', 1);
		++i;
	}
	if (!has_argument)
		ft_putchar_fd('\n', 1);
	return (0);
}
