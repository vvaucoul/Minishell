/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:29:27 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/13 20:02:49 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_end_str(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (!(ft_strcmp(tab[i], "<<")))
		{
			if (tab[i + 1])
			return (tab[i + 1]);
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

static int	get_tab_size(char **tab)
{
	int mx;
	int x;
	int i;

	mx = 0;
	x = 0;
	i = 0;

	while (tab[i])
	{
		x = ft_strlen(tab[i]);
		if (x > mx)
		mx = x;
		++i;
	}
	return (i * mx);
}

static	int	execute_redirection_bonus(char **tab_exec, char **tab_redir, char **envp)
{
	int		pid;
	int		state;
	int		fd;

	//fd = open((tab_exec)[1], O_RDONLY);
	if (!(pid = fork()))
	{
		dup2(fd, 0);
		execve(tab_exec[0], tab_exec, envp);
	}
	else
	{
		close(fd);
		waitpid(pid, &state, WUNTRACED);
	}
	return (0);
}

int		bonus_redirection(char **tab_exec, char **envp)
{
	char	**tab_redir;
	char	*end_str;
	char	*line;
	int i;

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
		ft_putstr_fd("> ", 1);
		line = read_line();
		tab_redir[i] = ft_strdup(line);
		free(line);
	}
	tab_redir[i] = NULL;
	return (execute_redirection_bonus(tab_exec, tab_redir, envp));
}
