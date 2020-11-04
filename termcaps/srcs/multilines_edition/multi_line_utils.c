/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:51:48 by user42            #+#    #+#             */
/*   Updated: 2020/11/04 13:23:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

int		get_cursor_row_position(t_line *line)
{
	int cursor_pos;

	cursor_pos = (get_term_struct()->term_size.col -
	get_term_struct()->prompt_len) - line->cursor_position;
	return (cursor_pos);
}

int		mlm_add_new_line(t_line *line)
{
	tputs(tgoto(tgetstr("do", NULL), 0, 1), 0, &term_putchar);
	++line->max_row;
	++line->start.row;
	set_curpos(line);
	return (0);
}
