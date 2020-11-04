/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_specials.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:33:49 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 16:39:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** First and last pipes are specials
*/

int			first_pipe(t_mns *mns, t_pipe *pipe_s)
{
	pipe(pipe_s->fd_current);
	pid_update(fork());
	pipe_s->ac_pipes[pipe_s->current_pipe].pid = pid_getpid();
	if (pid_getpid() == -1)
		display_errno_error();
	if (!(pid_getpid()))
	{
		close(pipe_s->fd_current[0]);
		dup2(pipe_s->fd_current[1], STDOUT_FILENO);
		exec_command(pipe_s->pipe_tab[pipe_s->current_pipe], mns);
		exit(mns->last_return);
	}
	close(pipe_s->fd_current[1]);
	pipe_s->fd_prev = pipe_s->fd_current[0];
	pipe_s->ac_pipes[pipe_s->current_pipe].pid = pid_getpid();
	++pipe_s->current_pipe;
	return (0);
}

int			last_pipe(t_mns *mns, t_pipe *pipe_s)
{
	int		i;

	pid_update(fork());
	pipe_s->ac_pipes[pipe_s->current_pipe].pid = pid_getpid();
	if (pid_getpid() == -1)
		display_errno_error();
	if (!pid_getpid())
	{
		dup2(pipe_s->fd_prev, STDIN_FILENO);
		exec_command(pipe_s->pipe_tab[pipe_s->current_pipe], mns);
		exit(mns->last_return);
	}
	close(pipe_s->fd_current[0]);
	i = 0;
	while (i <= pipe_s->nb_pipe)
	{
		waitpid(pipe_s->ac_pipes[i].pid, &pipe_s->ac_pipes[i].status, 0);
		++i;
	}
	return (0);
}
