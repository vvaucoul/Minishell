/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line_edition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:46:37 by user42            #+#    #+#             */
/*   Updated: 2020/11/04 10:42:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

void	multi_line_manager(t_line *line)
{
	if (get_cursor_row_position(line) <= 0)
	{
		cursor_to_start(line);
		++line->max_row;
		mlm_add_new_line(line);
	}
}

void	ml_line_prev(t_line *line)
{
	if (line->start.row > line->origin.row + 1)
		--line->start.row;
	set_curpos(line);
}

void	ml_line_next(t_line *line)
{
	if (line->start.row > line->origin.row && line->start.row < line->max_row)
	{
		++line->start.row;
		tputs(tgoto(tgetstr("do", NULL), 0, 1), 0, &term_putchar);
	}
	set_curpos(line);
}
