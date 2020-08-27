/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:27:53 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/27 18:09:48 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		b_exit(t_mns *mns)
{
	(void)mns;
	// free all minishell
	// system("leaks minishell");
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}
