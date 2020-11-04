/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_display_errors_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 18:50:39 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 16:46:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** WARNING
*/

static void		display_start_warning(void)
{
	ft_putstr_fd(MNS_COLOR_YELLOW, 2);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(MNS_COLOR_NOC, 2);
}

int				display_warning_tf(char *str, char *cmd, char *str_bonus,
int r_value)
{
	display_start_warning();
	if (str)
		ft_putstr_fd(str, 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (str_bonus)
		ft_putstr_fd(str_bonus, 2);
	ft_putstr_fd("\n", 2);
	return (r_value);
}

/*
** ERROR
*/

int				display_error_tf(char *str, char *cmd, char *str_bonus,
int r_value)
{
	display_start_error();
	if (str)
		ft_putstr_fd(str, 2);
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (str_bonus)
		ft_putstr_fd(str_bonus, 2);
	ft_putstr_fd("\n", 2);
	return (r_value);
}

void			display_start_error(void)
{
	ft_putstr_fd(MNS_COLOR_RED, 2);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(MNS_COLOR_NOC, 2);
}
