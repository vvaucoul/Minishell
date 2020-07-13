/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:29:27 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/13 22:52:41 by vvaucoul         ###   ########.fr       */
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

// A finir

static	int	execute_redirection_bonus(char **tab_exec, char **tab_redir, char **envp)
{
	int		pid;
	int		state;
	int		fd;

	tab_exec = r_update_redirection_tab(tab_exec, envp, "<<");
	tab_exec = r_get_tab_without_redirection(tab_exec);

	print_table(tab_redir, "tab_redir");
	print_table(tab_exec, "tab_exec");
	//fd = open((tab_exec)[1], O_RDONLY);

	char *tmp[] = {tab_exec[0], "1","4", "2", 0};
	print_table(tmp, "tab tmp");

	fd = open(0, O_RDONLY);

	if (!(pid = fork()))
	{
		dup2(fd, 0);
		close(fd);
		execve(tab_exec[0], tmp, NULL);
	}
	else
	{
		close(fd);
		waitpid(pid, &state, WUNTRACED);
	}
	return (0);
}

/*
char *argv[] = { "/bin/bash", "-c", "/usr/bin/cat <<EOF\ntest\nEOF", 0};
old - char *argv[] = { "/usr/bin/cat", "<<", "EOF", 0 };
  char *envp[] =
  {
	  "HOME=/",
	  "PATH=/bin:/usr/bin",
	  "USER=julekgwa",
	  0
  };
  int fd = open(0, O_RDONLY);
  dup2(fd, 0);
  close(fd);
  execve(argv[0], &argv[0], envp);
  fprintf(stderr, "Oops!\n");
  return -1;
*/

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
		++i;
	}
	tab_redir[--i] = NULL;
	return (execute_redirection_bonus(tab_exec, tab_redir, envp));
}
