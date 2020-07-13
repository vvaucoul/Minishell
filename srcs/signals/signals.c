/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:46:51 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/13 17:00:13 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		ft_putendl_fd("", 1);
		wait(0);
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
	if (signal(SIGQUIT, handle_signals) == SIG_ERR)
	display_error("Can't catch signal : SIGQUIT");
	if (signal(SIGWINCH, handle_signals) == SIG_ERR)
	display_error("Can't catch signal : SIGWINCH");

	return (0);
}

/*
void		sig_handler(int sig)
{
	t_editor	*ed;

	ed = get_editor();
	if (sig == SIGINT)
	{
		if (get_shell_env()->last_unmatched)
			get_shell_env()->del_input = 1;
		get_shell_env()->last_unmatched = NO_ERROR;
		init_editor();
		refresh_line(ed);
		wait(0);
		if (errno == ECHILD)
		{
			ft_putchar('\n');
			put_line(ed);
		}
	}
}
*/
