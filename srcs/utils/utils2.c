/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:50:58 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/11 16:52:38 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		display_error(char *str)
{
	if (!str)
		return (-1);
	else
	{
		ft_putstr_fd("[❌] minishell : ", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
