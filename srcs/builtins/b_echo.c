/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 15:27:30 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/10/31 22:50:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		find_first_arg(char **tabl)
{
	int i;

	i = 1;
	while (tabl[i])
	{
		if ((ft_strcmp(tabl[i], "-n")))
			return (i);
		++i;
	}
	return (i);
}

static int		cmd_has_arg(char **tabl)
{
	int i;

	if ((ft_strcmp(tabl[0], "echo")))
		return (-1);
	i = 1;
	while (tabl[i])
	{
		if (!(ft_strcmp(tabl[i], "-n")))
			return (TRUE);
		else
			return (FALSE);
		++i;
	}
	return (FALSE);
}

static int		init_echo(t_mns *mns, char **tabl, int *has_arg, int *i)
{
	update_last_return(mns, 0);
	if (!tabl)
	{
		ft_putstr_fd("\n", 1);
		return (FALSE);
	}
	*i = find_first_arg(tabl);
	if (((*has_arg) = cmd_has_arg(tabl)) < 0 || (!tabl[*i] && !(*has_arg)))
	{
		ft_putstr_fd("\n", 1);
		return (FALSE);
	}
	update_last_return(mns, 1);
	return (TRUE);
}

int				b_echo(t_mns *mns, char **tabl)
{
	int		has_arg;
	char	*epured_str;
	int		i;

	if ((init_echo(mns, tabl, &has_arg, &i)) != TRUE)
		return (1);
	while (tabl[i])
	{
		epured_str = rm_quotes(tabl[i]);
		ft_putstr_fd(epured_str, 1);
		free(epured_str);
		if (tabl[i + 1])
			ft_putchar_fd(' ', 1);
		++i;
	}
	if (!has_arg)
		ft_putchar_fd('\n', 1);
	update_last_return(mns, 0);
	return (1);
}
