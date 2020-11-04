/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:32:45 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 20:04:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Redirection 01
**
**	">"
**	EX : ps > s
*/

/*
** Exec command redirections
*/

int				apply_redirection(t_mns *mns, t_redirection *redir)
{
	int		state;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (!pid)
	{
		exec_command(redir->cmd_tab, mns);
		exit(get_last_return(mns));
	}
	else if (pid > 0)
	{
		waitpid(pid, &state, 0);
		check_signal(state);
	}
	update_last_return(mns, WEXITSTATUS(state));
	return (0);
}

/*
** Exec redirections
*/

static int		redirection_left(t_mns *mns, t_redirection *redir, int i)
{
	int fd;

	fd = 0;
	++redir->actu_redir;
	if ((fd = open(redir->final_redir_tab[i + 1], O_RDONLY, 0644)) == -1)
	{
		redir->redir_valid = 2;
		return (-1);
	}
	if (dup2(fd, 0) == -1)
	{
		redir->redir_valid = 3;
		ft_putstr_fd("Fatal error redirection !", 2);
		exit(errno);
	}
	if (redir->actu_redir == redir->nb_redir)
		if ((apply_redirection(mns, redir)) == -1)
		{
			close(fd);
			return (-1);
		}
	redir->redir_valid = TRUE;
	close(fd);
	return (0);
}

static int		redirection_right(t_mns *mns, t_redirection *redir, int i,
t_bool is_double)
{
	int fd;

	fd = 0;
	++redir->actu_redir;
	if ((fd = open(redir->final_redir_tab[i + 1], (is_double ? (O_CREAT |
	O_WRONLY | O_APPEND) : (O_CREAT | O_WRONLY | O_TRUNC)), 0644)) == -1)
	{
		redir->redir_valid = 2;
		return (-1);
	}
	if (dup2(fd, 1) == -1)
	{
		redir->redir_valid = 3;
		ft_putstr_fd("Fatal error redirection !", 2);
		exit(errno);
	}
	if (redir->actu_redir == redir->nb_redir)
		if ((apply_redirection(mns, redir)))
		{
			close(fd);
			return (-1);
		}
	redir->redir_valid = TRUE;
	close(fd);
	return (0);
}

/*
** Parse redirection
*/

t_bool			parse_redirections(t_mns *mns, t_redirection *redir)
{
	int i;

	i = 0;
	while (redir->final_redir_tab[i])
	{
		if (!(ft_strcmp(redir->final_redir_tab[i], ">")))
			if (redirection_right(mns, redir, i, FALSE) == -1)
				return (FALSE);
		if (!(ft_strcmp(redir->final_redir_tab[i], ">>")))
			if (redirection_right(mns, redir, i, TRUE) == -1)
				return (FALSE);
		if (!(ft_strcmp(redir->final_redir_tab[i], "<")))
			if (redirection_left(mns, redir, i) == -1)
				return (FALSE);
		if (BONUS)
		{
			if (!(ft_strcmp(redir->final_redir_tab[i], "<<")))
				return (bonus_redirection(mns, redir));
		}
		++i;
	}
	return (TRUE);
}

/*
** Main redirection
*/

int				main_redirections(t_mns *mns, char **tabl)
{
	t_redirection	redir;
	int				stdout_copy_in;
	int				stdout_copy_out;

	update_last_return(mns, 0);
	if (redirections_error(tabl))
		return (1 | update_last_return(mns, 2));
	stdout_copy_out = dup(STDOUT_FILENO);
	stdout_copy_in = dup(STDIN_FILENO);
	redir = init_redirection_struct(tabl, mns->envp);
	parse_redirections(mns, &redir);
	if (redir.redir_valid != TRUE)
	{
		if (redir.redir_valid == 2)
			update_last_return(mns, 1);
		display_errno_error();
	}
	dup2(stdout_copy_out, STDOUT_FILENO);
	dup2(stdout_copy_in, STDIN_FILENO);
	close(stdout_copy_in);
	close(stdout_copy_out);
	free_redirections(&redir);
	return (1);
}
