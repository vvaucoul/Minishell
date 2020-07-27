/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_line_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:35:28 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/27 18:00:26 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

int		cmp_keys(t_line *line, int key_pressed)
{
	// basic, insert & delete char
	if (key_pressed >= 32 && key_pressed <= 126)
		insert_char(line, key_pressed);
	else if (key_pressed == KEY_DC || key_pressed == 127)
		delete_char(line, key_pressed);

	// move cursor left / right
	else if (key_pressed == KEY_LEFT)
	cursor_to_left(line);
	else if (key_pressed == KEY_RIGHT)
	cursor_to_right(line);

	// home & end
	else if (key_pressed == KEY_HOME)
	cursor_to_start(line);
	else if (key_pressed == KEY_END)
	cursor_to_end(line);

	// history
	else if (key_pressed == KEY_UP)
	history_manager(line, TRUE, FALSE);
	else if (key_pressed == KEY_DOWN)
	history_manager(line, FALSE, FALSE);

	// shift left right
	else if (key_pressed == KEY_SLEFT)
	shift_word_left(line);
	else if (key_pressed == KEY_SRIGHT)
	shift_word_right(line);

	// copy paste
	else if (key_pressed == KEY_INSERT_INDEX)
	copy_paste_manager(line, TRUE, 0);
	else if (key_pressed == KEY_CCOPY)
	copy_paste_manager(line, FALSE, 0);
	else if (key_pressed == KEY_CUT)
	copy_paste_manager(line, FALSE, 1);
	else if (key_pressed == KEY_PASTE)
	copy_paste_manager(line, FALSE, 2);

	// clear
	else if (key_pressed == KEY_CTRLL)
	{
		tputs(tgoto(tgetstr("SF", NULL), 0, line->start.row - 1)
		, 1, &term_putchar);
		line->start.row = 1;
		set_curpos(line);
	}
	// valid line
	else if (key_pressed == '\n')
	{
		//insert_char(line, key_pressed);
		//multi_line_manager(line, FALSE, 0, TRUE);
		add_in_history(line->cmd);
		history_manager(line, FALSE, TRUE);
		printf("\ncmd line [%s]\n", line->cmd);
		return (FALSE);
	}
	return (TRUE);
}
