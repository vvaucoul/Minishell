/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:09:41 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/06 16:48:34 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

int		line_shift_right(t_line *line)
{
	int		start;
	int		len;

	start = line->cursor_position - PROMPT_LEN - 1;
	len = ft_strlen(line->cmd);
	while (len > start)
	{
		line->cmd[len + 1] = line->cmd[len];
		--len;
	}
	return (0);
}

int		line_shift_left(t_line *line)
{
	int		start;
	int		len;

	start = line->cursor_position - PROMPT_LEN;
	len = ft_strlen(line->cmd);
	while (start < len)
	{
		line->cmd[start] = line->cmd[start + 1];
		++start;
	}
	return (0);
}

void	init_line_position(t_line *line)
{
	char	answer[20];
	int		i;

	write(0, "\e[6n", 5);
	bzero(answer, 20);
	i = read(0, answer, 20);
	answer[i] = 0;
	i = 2;
	line->start.row = atoi(answer + i);
	while (isdigit(answer[i]))
		i++;
	line->start.col = atoi(answer + i + 1);
}

t_line	*init_new_line(void)
{
	static t_line	line;
	int				i;

	line.cursor_position = PROMPT_LEN;
	line.len = 0;
	line.start.row = 0;
	line.start.col = PROMPT_LEN;
	i = -1;
	while (i++ < MAX_LINE_LEN)
		line.cmd[i] = '\0';
	init_line_position(&line);
	return (&line);
}
