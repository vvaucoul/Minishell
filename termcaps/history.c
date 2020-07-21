/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:58:21 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/21 20:33:50 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

/*
** Utils
*/

int		create_history_file()
{
	int fd;

	return ((fd = open(HIST_FILE_NAME, O_CREAT, 0644)));
}

static int		open_history_file()
{
	return (open(HIST_FILE_NAME, O_APPEND | O_RDWR));
}

/*
**	Append line to history file
*/

int		add_in_history(char *str)
{
	int fd;

	fd = open_history_file();
	write(fd, str, strlen(str)); //function
	write(fd, "\n", 1);
	return (0);
}

/*
**	Read lines
*/

static char 	*create_history_str()
{
	int			fd;
	int			i;
	char		buff;
	char		*str;

	fd = open_history_file();
	i = 0;
	while (read(fd, &buff, 1) > 0)
	++i;
	close(fd);
	fd = open_history_file();
	if (!(str = malloc(sizeof(char) * (i + 1))))
	return (NULL);
	while (read(fd, &buff, 1) > 0)
	{
		str[i] = buff;
		++i;
	}
	return (str);
}

static int	get_history_line(t_line *line, int line_to_found)
{
	char	*str;
	int		ac;
	int		i;
	int		li;

	str = create_history_str();
	ac = 0;
	i = 0;
	if (line_to_found > 0)
	{
		while (ac < line_to_found)
		{
			if (str[i] == '\n')
				++ac;
			++i;
		}
	}
	++i;
	li = 0;
	while (str[i] != '\n' && str[i])
	{
		line->cmd[li] = str[i];
		++li;
		++i;
	}
	line->cmd[li] = 0;
	return (0);
}

static int		get_last_history_line()
{
	int			fd;
	char		buff;
	int			line;

	fd = open_history_file();
	line = 0;
	while (read(fd, &buff, 1) > 0)
	{
		if (buff == '\n')
		++line;
	}
	return (line);
}

/*
**	up_down = 1 --> up
**	up_down = 0 --> down
*/

int		history_manager(t_line *line, int up_down)
{
	static int	init = 0;
	static int	hist_line = 0;
	static int	hist_len = 0;

	if (!init)
	{
		hist_line = get_last_history_line();
		hist_len = hist_line;
		++init;
	}
	if (up_down)
	{
		if (hist_line > 0)
		--hist_line;
	}
	else
	{
		if (hist_line < hist_len)
		++hist_line;
	}
	delete_full_line(line);
	get_history_line(line, hist_line);
	ft_putstr_fd(line->cmd, 0);
	return (0);
}
