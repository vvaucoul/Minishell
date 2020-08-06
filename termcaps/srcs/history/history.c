/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:58:21 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/06 16:45:46 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

/*
** Utils
*/

static int		open_history_file(void)
{
	return (open(HIST_FILE_NAME, O_APPEND | O_RDWR | O_CREAT, 0644));
}

/*
**	Append line to history file
*/

int				add_in_history(char *str)
{
	int fd;

	fd = open_history_file();
	if (ft_strcmp(str, "\0"))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
	close(fd);
	return (0);
}

/*
**	Read lines
*/

static int		get_history_line(t_line *line, int line_to_found)
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
		free(buffer);
	}
	free(buffer);
	close(fd);
	return (0);
}

int				get_last_history_line(void)
{
	int			fd;
	char		*buff;
	int			line;

	fd = open_history_file();
	line = 0;
	while (get_next_line(fd, &buff) > 0)
	{
		++line;
		free(buff);
	}
	free(buff);
	close(fd);
	return (line);
}

/*
**	up_down = 1 --> up
**	up_down = 0 --> down
*/

int				history_manager(t_line *line, int up_down, int reset)
{
	static int			init = 0;
	static t_history	hist;

	if (!(history_init(reset, &init, up_down, &hist)))
		return (0);
	delete_full_line(line);
	line = init_new_line();
	get_history_line(line, hist.actu_hist_line);
	return (0);
}
