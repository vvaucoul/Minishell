/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_display_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:50:58 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 16:50:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		display_errno_error(void)
{
	return (display_error(strerror(errno)));
}

int		display_error(char *str)
{
	if (!str)
		return (-1);
	else
	{
		ft_putstr_fd(MNS_COLOR_RED, 2);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(MNS_COLOR_NOC, 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	return (0);
}

int		display_error_cmd(char *str)
{
	if (!str)
		return (-1);
	else
	{
		ft_putstr_fd(MNS_COLOR_RED, 2);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(MNS_COLOR_NOC, 2);
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	return (0);
}

int		display_error_arg(char *str, char *cmd)
{
	if (!str || !cmd)
		return (-1);
	else
	{
		ft_putstr_fd(MNS_COLOR_RED, 2);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(MNS_COLOR_NOC, 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	return (0);
}

int		display_malloc_error(void)
{
	ft_putstr_fd(MNS_COLOR_RED, 2);
	ft_putstr_fd("minishell: malloc error, minishell saved your \
	computer ! ", 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(MNS_COLOR_NOC, 2);
	return (0);
}
