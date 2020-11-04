/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:44:41 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/04 13:21:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

void	insert_char(t_line *line, int key_pressed)
{
	if ((line->len + 1) >= MAX_LINE_LEN)
		return ;
	line_shift_right(line);
	line->cmd[line->cursor_position -
	get_term_struct()->prompt_len] = key_pressed;
	++line->len;
	++line->cursor_position;
	tputs(tgetstr("im", NULL), 1, &term_putchar);
	write(0, &key_pressed, 1);
	tputs(tgetstr("ei", NULL), 1, &term_putchar);
	if (MULTILINE)
		multi_line_manager(line);
}

void	delete_char(t_line *line, int key_pressed)
{
	if (key_pressed == 127 && line->cursor_position ==
	get_term_struct()->prompt_len)
		return ;
	if (key_pressed == 127)
		cursor_to_left(line);
	if (line->cursor_position == line->len + get_term_struct()->prompt_len)
		return ;
	line_shift_left(line);
	--line->len;
	tputs(tgetstr("cd", NULL), 0, &term_putchar);
	ft_putstr_fd(line->cmd + (line->cursor_position -
	get_term_struct()->prompt_len), 0);
	set_curpos(line);
	if (MULTILINE)
		multi_line_manager(line);
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
	line->cursor_position = get_term_struct()->prompt_len;
	line->start.col = get_term_struct()->prompt_len;
	set_curpos(line);
	tputs(tgetstr("cd", NULL), 0, &term_putchar);
	ft_putstr_fd(line->cmd, 0);
	if (MULTILINE)
		multi_line_manager(line);
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
	if (MULTILINE)
		multi_line_manager(line);
}
