/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:50:58 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/11 18:39:45 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		display_error(char *str)
{
	if (!str)
		return (-1);
	else
	{
		ft_putstr(COLOR_RED);
		ft_putstr_fd("[❌] minishell 💥: ", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
		ft_putstr(COLOR_NOC);
	}
	return (0);
}

int		display_error_cmd(char *str)
{
	if (!str)
		return (-1);
	else
	{
		ft_putstr(COLOR_RED);
		ft_putstr_fd("[❌] minishell 💥: command not found: ", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
		ft_putstr(COLOR_NOC);
	}
	return (0);
}
