/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:29:27 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 20:03:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Heredoc File
*/

static	int		write_heredoc_file(char **heredoc)
{
	char	*tmp;
	int		fd;
	int		i;

	i = 0;
	fd = open(RANDOM_TMP_STRING, O_WRONLY | O_TRUNC | O_CREAT, 0755);
	while (heredoc[i])
	{
		ft_putstr_fd(tmp = ft_strjoin(heredoc[i], "\n"), fd);
		free(tmp);
		++i;
	}
	ft_putstr_fd("\0", fd);
	close(fd);
	return (0);
}

/*
** Redirection <<
*/

static	int		execute_redirection_bonus(t_mns *mns, t_redirection *redir,
char **tab_exec)
{
	char	*exec_table[3];
	int		pid;
	int		state;
	int		fd;

	fd = open(RANDOM_TMP_STRING, O_RDONLY);
	exec_table[0] = ft_strdup(tab_exec[0]);
	exec_table[1] = ft_strdup(RANDOM_TMP_STRING);
	exec_table[2] = NULL;
	if (!(pid = fork()))
	{
		dup2(fd, 0);
		close(fd);
		exec_command(redir->cmd_tab, mns);
	}
	else
	{
		close(fd);
		waitpid(pid, &state, WUNTRACED);
	}
	multi_free(exec_table[0], exec_table[1], NULL, NULL);
	return (0);
}

/*
**	Call redirection
**	Get heredoc inputs
*/

static	void	bonus_redirection_heredoc(char **tab_redir, char *end_str)
{
	int		i;

	i = 0;
	while (TRUE)
	{
		ft_putstr_fd("heredoc > ", 1);
		tab_redir[i] = read_line();
		if (tab_redir[i])
		{
			if (!(ft_strcmp(tab_redir[i], end_str)))
				break ;
		}
		++i;
	}
	free(tab_redir[i]);
	tab_redir[i] = NULL;
}

/*
** Main bonus redirection
*/

int				bonus_redirection(t_mns *mns, t_redirection *redir)
{
	char	**tab_redir;
	char	*end_str;

	update_last_return(mns, 0);
	++redir->actu_redir;
	if (!(end_str = get_end_str(redir->final_redir_tab)))
	{
		display_error("parse error near '\\n'");
		return (0);
	}
	if (!(tab_redir = malloc(sizeof(char *) *
	(ft_full_tablen(redir->final_redir_tab) + MAX_CHAR_IN_PROMPT))))
		return (-1);
	bonus_redirection_heredoc(tab_redir, end_str);
	write_heredoc_file(tab_redir);
	execute_redirection_bonus(mns, redir, redir->final_redir_tab);
	ft_freetab(tab_redir);
	redir->redir_valid = TRUE;
	return (0);
}
