/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_line_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:35:28 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/06 16:55:21 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

int		cmp_specials_keys(t_line *line, int key_pressed)
{
	if (key_pressed == KEY_HOME)
		cursor_to_start(line);
	else if (key_pressed == KEY_END)
		cursor_to_end(line);
	else if (key_pressed == KEY_UP)
		history_manager(line, TRUE, FALSE);
	else if (key_pressed == KEY_DOWN)
		history_manager(line, FALSE, FALSE);
	else if (key_pressed == KEY_SLEFT)
		shift_word_left(line);
	else if (key_pressed == KEY_SRIGHT)
		shift_word_right(line);
	else if (key_pressed == KEY_INSERT_INDEX)
		copy_paste_manager(line, TRUE, 0);
	else if (key_pressed == KEY_CCOPY)
		copy_paste_manager(line, FALSE, 0);
	else if (key_pressed == KEY_CUT)
		copy_paste_manager(line, FALSE, 1);
	else if (key_pressed == KEY_PASTE)
		copy_paste_manager(line, FALSE, 2);
	return (0);
}

int		cmp_keys(t_line *line, int key_pressed)
{
	if (key_pressed >= 32 && key_pressed <= 126)
		insert_char(line, key_pressed);
	else if (key_pressed == KEY_DC || key_pressed == 127)
		delete_char(line, key_pressed);
	else if (key_pressed == KEY_LEFT)
		cursor_to_left(line);
	else if (key_pressed == KEY_RIGHT)
		cursor_to_right(line);
	cmp_specials_keys(line, key_pressed);
	if (key_pressed == KEY_CTRLL)
	{
		tputs(tgoto(tgetstr("SF", NULL), 0, line->start.row - 1)
		, 1, &term_putchar);
		line->start.row = 1;
		set_curpos(line);
	}
	else if (key_pressed == '\n')
	{
		add_in_history(line->cmd);
		history_manager(line, FALSE, TRUE);
		return (FALSE);
	}
	return (TRUE);
}
