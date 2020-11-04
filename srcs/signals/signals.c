/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:46:51 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/04 22:35:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mns	**get_signal_mns(t_mns *real_mns, t_bool init)
{
	static t_mns *mns;

	if (init)
		mns = real_mns;
	return (&mns);
}

static void		handle_signal_int(int signal)
{
	ft_putstr_fd("\b\b  \b\b", 2);
	if (signal == SIGINT)
	{
		update_last_return(*get_signal_mns(NULL, FALSE), 130);
		if (pid_getpid())
		{
			kill(pid_getpid(), SIGINT);
			pid_update(0);
			ft_putchar_fd('\n', 1);
		}
		else
		{
			ft_putchar_fd('\n', 1);
			display_prompt();
		}
	}
	update_last_return(*get_signal_mns(NULL, FALSE), 130);
}

static void		handle_signal_quit(int signal)
{
	ft_putstr_fd("\b\b  \b\b", 2);
	if (signal == SIGQUIT)
	{
		update_last_return(*get_signal_mns(NULL, FALSE), 131);
		if (pid_getpid())
		{
			kill(pid_getpid(), SIGQUIT);
			pid_update(0);
			ft_putstr_fd("Quit (core dumped)\n", 1);
		}
	}
	update_last_return(*get_signal_mns(NULL, FALSE), 131);
}

void			reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}

int				init_signals_handle(t_mns *mns)
{
	get_signal_mns(mns, TRUE);
	if (signal(SIGINT, handle_signal_int) == SIG_ERR)
		display_error("Can't catch signal : SIGINT");
	if (signal(SIGQUIT, handle_signal_quit) == SIG_ERR)
		display_error("Can't catch signal : SIGQUIT");
	return (0);
}
