/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 19:23:09 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 20:38:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Loop Middle Pipes
*/

static int			do_pipes(t_mns *mns, t_pipe *pipe_s)
{
	while (pipe_s->pipe_tab[pipe_s->current_pipe + 1])
	{
		pipe(pipe_s->fd_current);
		pid_update(fork());
		pipe_s->ac_pipes[pipe_s->current_pipe].pid = pid_getpid();
		if (pid_getpid() == -1)
			display_errno_error();
		if (!(pid_getpid()))
		{
			close(pipe_s->fd_current[0]);
			dup2(pipe_s->fd_prev, STDIN_FILENO);
			dup2(pipe_s->fd_current[1], STDOUT_FILENO);
			exec_command(pipe_s->pipe_tab[pipe_s->current_pipe], mns);
			exit(mns->last_return);
		}
		close(pipe_s->fd_current[1]);
		close(pipe_s->fd_prev);
		pipe_s->fd_prev = pipe_s->fd_current[0];
		++pipe_s->current_pipe;
	}
	return (0);
}

static int			end_pipe_status(t_mns *mns, t_pipe *pipe_s)
{
	update_last_return(mns,
	WEXITSTATUS(pipe_s->ac_pipes[pipe_s->nb_pipe].status));
	return (0);
}

/*
** Main pipe function
*/

int					p_pipe(t_mns *mns, char **tab_exec)
{
	t_pipe	pipe;
	int		stdout_copy_in;
	int		stdout_copy_out;

	if (pipes_valid(tab_exec))
		return (update_last_return(mns, display_error_tf(E_PS, NULL, NULL, 2)));
	if ((init_pipe_struct(&pipe, tab_exec)))
		return (display_error_tf("Malloc error", NULL, NULL, -1));
	stdout_copy_out = dup(STDOUT_FILENO);
	stdout_copy_in = dup(STDIN_FILENO);
	first_pipe(mns, &pipe);
	do_pipes(mns, &pipe);
	last_pipe(mns, &pipe);
	end_pipe_status(mns, &pipe);
	dup2(stdout_copy_out, STDOUT_FILENO);
	dup2(stdout_copy_in, STDIN_FILENO);
	close(stdout_copy_in);
	close(stdout_copy_out);
	pid_update(0);
	free_pipes(&pipe);
	return (1);
}
