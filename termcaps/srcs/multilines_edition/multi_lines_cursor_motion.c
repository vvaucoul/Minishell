/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_lines_cursor_motion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 18:50:51 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/28 17:42:47 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static void ml_cm_update_cursor_position(t_line *line, int index)
{
	tputs(tgoto(tgetstr("cm", NULL), line->cursor_position,
	line->start.row - 1), 0, &term_putchar);
}

void 	ml_cm_left(t_line **ml_lines, int index)
{
	if (ml_lines[index]->cursor_position <= PROMPT_LEN)
		return ;
	--ml_lines[index]->cursor_position;
	ml_cm_update_cursor_position(ml_lines[index], index);
}

void 	ml_cm_right(t_line **ml_lines, int index)
{
	if (ml_lines[index]->cursor_position >= ml_lines[index]->len + PROMPT_LEN)
		return ;
	++ml_lines[index]->cursor_position;
	ml_cm_update_cursor_position(ml_lines[index], index);
}

void 	ml_cm_start(t_line **ml_lines, int index)
{
	ml_lines[index]->cursor_position = PROMPT_LEN;
	ml_cm_update_cursor_position(ml_lines[index], index);
}

void 	ml_cm_end(t_line **ml_lines, int index)
{
	ml_lines[index]->cursor_position = ml_lines[index]->len + PROMPT_LEN;
	ml_cm_update_cursor_position(ml_lines[index], index);
}
