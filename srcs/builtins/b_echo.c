/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 15:27:30 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/27 18:09:02 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		find_first_arg(char **tabl, T_BOOL has_argument)
{
	int i;

	i = 0;
	while (tabl[i])
	{
		if (!(ft_strcmp(tabl[i], "echo")))
			return (i + (has_argument ? 2 : 1));
		++i;
	}
	return (i);
}

static T_BOOL	cmd_has_argument(char **tabl)
{
	int i;

	i = 0;
	while (tabl[i])
	{
		if (!(ft_strcmp(tabl[i], "-n")) && (!(ft_strcmp(tabl[i - 1], "echo")))
		&& i == 1)
			return (TRUE);
		++i;
	}
	return (FALSE);
}

int				b_echo(char **tabl)
{
	T_BOOL	has_argument;
	char	*epured_str;
	int		i;

	if (!tabl)
		return (0);
	has_argument = cmd_has_argument(tabl);
	i = find_first_arg(tabl, has_argument);
	if (!tabl[i] && has_argument)
		return (0);
	while (tabl[i])
	{
		if (!(epured_str = epur_b_str(tabl[i])))
			return (-1);
		ft_putstr_fd(epured_str, 1);
		free(epured_str);
		if (tabl[i + 1])
			ft_putchar_fd(' ', 1);
		++i;
	}
	if (!has_argument)
		ft_putchar_fd('\n', 1);
	return (0);
}
