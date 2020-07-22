/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:58:21 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/22 18:33:06 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

/*
** Utils
*/

static int		open_history_file()
{
	return (open(HIST_FILE_NAME, O_APPEND | O_RDWR | O_CREAT, 0644));
}

/*
**	Append line to history file
*/

int		add_in_history(char *str)
{
	int fd;

	fd = open_history_file();
	if (strcmp(str, "\0")) // function
	{
		write(fd, str, strlen(str)); //function
		write(fd, "\n", 1);
	}
	close(fd);
	return (0);
}

/*
**	Read lines
*/

static int get_history_line(t_line *line, int line_to_found)
{
	int		fd;
	char	*buffer;
	int		ac_line;

	fd = open_history_file();
	ac_line = 0;
	while (get_next_line(fd, &buffer) > 0)
	{
		if (ac_line == line_to_found)
		{
			close(fd);
			insert_full_line(line, buffer);
			return (0);
		}
		++ac_line;
	}
	close(fd);
	return (0);
}

static int		get_last_history_line()
{
	int			fd;
	char		*buff;
	int			line;

	fd = open_history_file();
	line = 0;
	while (get_next_line(fd, &buff) > 0)
	++line;
	close(fd);
	return (line);
}

/*
**	up_down = 1 --> up
**	up_down = 0 --> down
*/

// ICIiiiiiiiiiiiiiiiiiiiiiiiii finir l historique, plante et charge mal les lignes

int		history_manager(t_line *line, int up_down, int reset)
{
	static int init = 0;
	static int hist_len = 0;
	static int actu_hist_line = 0;

	if (reset)
	{
		init = 0;
		return (0);
	}
	if (!(init)++)
	{
		hist_len = get_last_history_line();
		actu_hist_line = hist_len;
	}
	if (up_down)
	{
		if (actu_hist_line > 0)
		--actu_hist_line;
	}
	else
	{
		if (actu_hist_line < hist_len)
		++actu_hist_line;
	}
	delete_full_line(line);
	line = init_new_line();
	get_history_line(line, actu_hist_line);
	return (0);
}
