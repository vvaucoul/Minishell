/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_display_returns.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:50:14 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 16:50:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*disperr_nul(char *str)
{
	ft_putstr_fd(MNS_COLOR_RED, 2);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(MNS_COLOR_NOC, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}
