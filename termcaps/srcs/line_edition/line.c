/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:44:41 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/06 16:49:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

void	insert_char(t_line *line, int key_pressed)
{
	if ((line->len + 1) >= MAX_LINE_LEN)
		return ;
	line_shift_right(line);
	line->cmd[line->cursor_position - PROMPT_LEN] = key_pressed;
	++line->len;
	++line->cursor_position;
	tputs(tgetstr("im", NULL), 1, &term_putchar);
	write(0, &key_pressed, 1);
	tputs(tgetstr("ei", NULL), 1, &term_putchar);
}

void	delete_char(t_line *line, int key_pressed)
{
	if (key_pressed == 127 && line->cursor_position == PROMPT_LEN)
		return ;
	if (key_pressed == 127)
		cursor_to_left(line);
	if (line->cursor_position == line->len + PROMPT_LEN)
		return ;
	line_shift_left(line);
	--line->len;
	tputs(tgetstr("cd", NULL), 0, &term_putchar);
	ft_putstr_fd(line->cmd + (line->cursor_position - PROMPT_LEN), 0);
	set_curpos(line);
}

void	delete_full_line(t_line *line)
{
	int i;

	i = 0;
	while (i < MAX_LINE_LEN)
	{
		line->cmd[i] = '\0';
		++i;
	}
	line->cursor_position = PROMPT_LEN;
	line->start.col = PROMPT_LEN;
	set_curpos(line);
	tputs(tgetstr("cd", NULL), 0, &term_putchar);
	ft_putstr_fd(line->cmd, 0);
}

void	insert_full_line(t_line *line, char *str)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		insert_char(line, str[i]);
		++i;
	}
	free(str);
}
