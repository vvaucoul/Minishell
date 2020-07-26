/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 17:00:07 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/26 19:06:00 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

void	ml_delete_char(t_line *line, int key_pressed)
{

}

void 	clear_multi_line_cmd(t_line **ml_lines)
{

}

void 	convert_multilines_to_line(t_line **ml_lines, t_line *line)
{

}

void 	insert_char_in_line(t_line **ml_lines, int start_y, int y, int key_pressed)
{
	int index;

	index = y - start_y;
	if (ml_lines[index]->len + 1 >= MAX_LINE_LEN)
	return ;
	line_shift_right(ml_lines[index]);
	ml_lines[index]->cmd[ml_lines[index]->cursor_position - PROMPT_LEN] = key_pressed;
	++ml_lines[index]->len;
	tputs(tgetstr("im", NULL), 1, &term_putchar);
	write(0, &key_pressed, 1);
	tputs(tgetstr("ei", NULL), 1, &term_putchar);
}

void 	delete_char_in_line(t_line **ml_lines, int start_y, int y, int key_pressed)
{
	int index;

	index = y - start_y;

}
