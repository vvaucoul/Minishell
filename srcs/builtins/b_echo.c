/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 15:27:30 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/06/26 16:25:50 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		b_echo(char **str, T_BOOL has_argument)
{
	int i;
	int j;

	if (!str)
		return (-1);
	i = 0;
	j = 0;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (str[i + 1])
			ft_putchar_fd(' ', 1);
		++i;
	}
	if (!has_argument)
		ft_putchar_fd('\n', 1);
	return (0);
}
