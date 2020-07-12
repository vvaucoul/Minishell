/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:46:51 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/12 14:26:04 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		ft_putendl_fd("", 1);
	}
}

void 	reset_signals()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}

int		init_signals_handle()
{
	signal(SIGINT, SIG_DFL);

	if (signal(SIGINT, handle_signals) == SIG_ERR)
	display_error("Can't catch signal : SIGINT");
	if (signal(SIGTSTP, handle_signals) == SIG_ERR)
	display_error("Can't catch signal : SIGTSTP");
	if (signal(SIGWINCH, handle_signals) == SIG_ERR)
	display_error("Can't catch signal : SIGWINCH");

	return (0);
}
