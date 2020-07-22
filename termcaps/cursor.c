/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 18:58:03 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/21 19:49:11 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

void	set_curpos(t_line *line)
{
	tputs(tgoto(tgetstr("cm", NULL), line->cursor_position,
	line->start.row - 1), 0, &term_putchar);
}

void	cursor_to_end(t_line *line)
{
	line->cursor_position = line->len + PROMPT_LEN;
	set_curpos(line);
}

void	cursor_to_start(t_line *line)
{
	line->cursor_position = PROMPT_LEN;
	set_curpos(line);
}

void	cursor_to_left(t_line *line)
{
	if (line->cursor_position <= PROMPT_LEN)
		return ;
	line->cursor_position--;
	set_curpos(line);
}

void	cursor_to_right(t_line *line)
{
	if (line->cursor_position >= line->len + PROMPT_LEN)
		return ;
	line->cursor_position++;
	set_curpos(line);
}
