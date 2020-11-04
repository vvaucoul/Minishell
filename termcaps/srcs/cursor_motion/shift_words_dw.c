/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_words_dw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:53:41 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 12:54:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static t_bool		is_validchar(char c)
{
	return ((c >= 33 && c <= 126) ? TRUE : FALSE);
}

void				swl_dw(t_line **line)
{
	while (!(is_validchar(line[0]->cmd[line[0]->cursor_position -
		get_term_struct()->prompt_len]))
	&& line[0]->cursor_position > get_term_struct()->prompt_len)
		--line[0]->cursor_position;
	while (is_validchar(line[0]->cmd[line[0]->cursor_position -
		get_term_struct()->prompt_len])
	&& line[0]->cursor_position > get_term_struct()->prompt_len)
		--line[0]->cursor_position;
}

void				swr_dw(t_line **line)
{
	while (!(is_validchar(line[0]->cmd[line[0]->cursor_position -
		get_term_struct()->prompt_len]))
	&& line[0]->cursor_position < line[0]->len + get_term_struct()->prompt_len)
		++line[0]->cursor_position;
	while (is_validchar(line[0]->cmd[line[0]->cursor_position -
		get_term_struct()->prompt_len])
	&& line[0]->cursor_position < line[0]->len + get_term_struct()->prompt_len)
		++line[0]->cursor_position;
}
