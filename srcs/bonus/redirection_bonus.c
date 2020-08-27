/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:29:27 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/27 16:48:55 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	BONUS Redirection Utils
*/

static char *get_end_str(char **tabl)
{
	int i;

	i = 0;
	while (tabl[i])
	{
		if (!(ft_strcmp(tabl[i], "<<")))
		{
			if (tabl[i + 1])
			return (tabl[i + 1]);
			else
			return (NULL);
		}
		++i;
	}
	return (NULL);
}

static char *read_line()
{
	char	buff;
	char 	line[MAX_CHAR_IN_PROMPT];
	int 	i;

	i = 0;
	buff = 0;
	while (buff != '\n')
	{
		read(0, &buff, 1);
		if (buff != '\n')
		{
			line[i] = buff;
			++i;
		}
	}
	line[i] = '\0';
	return (ft_strdup(line));
}

static int	get_tab_size(char **tabl)
{
	int mx;
	int x;
	int i;

	mx = 0;
	x = 0;
	i = 0;

	while (tabl[i])
	{
		x = ft_strlen(tabl[i]);
		if (x > mx)
		mx = x;
		++i;
	}
	return (i * mx);
}

/*
**	Heredoc File
*/

static	int	write_heredoc_file(char **heredoc)
{
	int fd;
	int i;

	i = 0;
	fd = open(RANDOM_TMP_STRING, O_WRONLY | O_TRUNC | O_CREAT, 0755);
	while (heredoc[i])
	{
		ft_putstr_fd(ft_strcat(heredoc[i], "\n"), fd);
		++i;
	}
	ft_putstr_fd("\0", fd);
	close(fd);
	return (0);
}

/*
** Redirection <<
*/

static	int	execute_redirection_bonus(char **tab_exec, char **tab_redir, char **envp)
{
	char	*exec_table[3];
	int		pid;
	int		state;
	int		fd;

	(void)tab_redir;

	tab_exec = r_update_redirection_tab(tab_exec, envp, "<<");
	tab_exec = r_get_tab_without_redirection(tab_exec);
//	print_table(tab_redir, "tab_redir");
//	print_table(tab_exec, "tab_exec");
	fd = open(RANDOM_TMP_STRING, O_RDONLY);
	exec_table[0] = ft_strdup(tab_exec[0]);
	exec_table[1] = ft_strdup(RANDOM_TMP_STRING);
	exec_table[2] = NULL;
	if (!(pid = fork()))
	{
		dup2(fd, 0);
		close(fd);
		execve(exec_table[0], exec_table, envp);
	}
	else
	{
		close(fd);
		waitpid(pid, &state, WUNTRACED);
	}
	return (0);
}

/*
**	Call redirection
**	Get heredoc inputs
*/

int		bonus_redirection(char **tab_exec, char **envp)
{
	char	**tab_redir;
	char	*end_str;
	char	*line;
	int		i;

	if (!(end_str = get_end_str(tab_exec)))
	{
		display_error("parse error near '\\n'");
		return (0);
	}
	if (!(tab_redir = malloc(sizeof(char *) * (get_tab_size(tab_exec) + 2))))
		return (-1);
	i = 0;
	while (ft_strcmp(line, end_str))
	{
		ft_putstr_fd("heredoc> ", 1);
		line = read_line();
		tab_redir[i] = ft_strdup(line);
		free(line);
		++i;
	}
	tab_redir[--i] = NULL;
	write_heredoc_file(tab_redir);
	return (execute_redirection_bonus(tab_exec, tab_redir, envp));
}
