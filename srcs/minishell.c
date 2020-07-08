/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 18:03:46 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/02 16:13:28 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	display_prompt(char **envp)
{
	ft_putstr_fd(COLOR_GREEN, 1);
	b_pwd(envp, FALSE);
	ft_putstr_fd(COLOR_CYAN, 1);
	ft_putstr_fd(" ➜  ", 1);
	ft_putstr_fd(COLOR_NOC, 1);
}

static char	*get_line(char *line)
{
	int		fc;
	char	buffer;
	int 	i;

	i = 0;
	while ((fc = read(1, &buffer, 1)))
	{
		if (buffer == '\n')
		{
			line[i] = '\0';
			return (line);
		}
		line[i] = buffer;
		++i;
	}
	return (line);
}

char	*create_path(char **envp, char *cmd)
{
	char	**all_path;
	char	*path;
	int		i;

	i = 0;
	all_path = ft_str_to_tab(get_env_value("PATH", envp), ':');
	while (all_path[i])
	{
		path = malloc(sizeof(char) * MAX_CHAR_IN_PROMPT);
		path = strcat(path, all_path[i]);
		path = strcat(path, "/");
		path = strcat(path, cmd);
		if (open(path, O_RDONLY) >= 0)
		return (path);
		++i;
	}
	return (cmd);
}

int		minishell(t_mns *mns)
{
	char	**tab_line;
	char	*line;
	char	*path;

	init_signals_handle();
	while (mns->is_running)
	{
		if (!(line = malloc(sizeof(char) * MAX_CHAR_IN_PROMPT)))
		return (-1);

		display_prompt(mns->envp);

		line = get_line(line);
		tab_line = ft_str_to_tab(line, ' ');

		path = create_path(mns->envp, tab_line[0]);

		run(mns, path, tab_line, mns->envp);

		free(tab_line);
		free(line);
		free(path);
	}
	return (0);
}
