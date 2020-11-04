/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:22:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 14:29:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static t_bool			is_validchar(char c)
{
	return ((c >= 33 && c <= 126) ? TRUE : FALSE);
}

/*
** Shift Word Left
*/

static int				shift_word_left_fl(t_line *line)
{
	if ((line->cursor_position - get_term_struct()->prompt_len - 1) == 0)
	{
		--line->cursor_position;
		if (line->cmd[(line->cursor_position -
		get_term_struct()->prompt_len - 1) + 2] != ' '
		&& line->cmd[(line->cursor_position -
		get_term_struct()->prompt_len - 1) + 1] == ' ')
			++line->cursor_position;
	}
	set_curpos(line);
	return (0);
}

int						shift_word_left(t_line *line)
{
	t_bool		is_in_word;
	int			scp;

	is_in_word = FALSE;
	scp = line->cursor_position;
	while (is_validchar(line->cmd[line->cursor_position -
	get_term_struct()->prompt_len]) &&
	line->cursor_position > get_term_struct()->prompt_len)
		--line->cursor_position;
	if (line->cursor_position != scp)
		is_in_word = TRUE;
	if (!(is_validchar(line->cmd[line->cursor_position -
	get_term_struct()->prompt_len - 1])))
		is_in_word = FALSE;
	if (!(is_in_word))
		swl_dw(&line);
	if (!(is_in_word))
		++line->cursor_position;
	else
		shift_word_left(line);
	return (shift_word_left_fl(line));
}

static int				shift_word_right_fl(t_line *line)
{
	while (is_validchar(line->cmd[line->cursor_position -
	get_term_struct()->prompt_len]) &&
	line->cursor_position < line->len + get_term_struct()->prompt_len)
		--line->cursor_position;
	++line->cursor_position;
	set_curpos(line);
	return (0);
}

int						shift_word_right(t_line *line)
{
	t_bool		is_in_word;
	int			scp;

	is_in_word = FALSE;
	scp = line->cursor_position;
	while (is_validchar(line->cmd[line->cursor_position -
	get_term_struct()->prompt_len]) &&
	line->cursor_position < line->len + get_term_struct()->prompt_len)
		++line->cursor_position;
	if (line->cursor_position != scp)
		is_in_word = TRUE;
	if (!(is_validchar(line->cmd[line->cursor_position -
	get_term_struct()->prompt_len + 1])))
		is_in_word = FALSE;
	if (!(is_in_word))
		swr_dw(&line);
	if (!(is_in_word))
		--line->cursor_position;
	else
		shift_word_right(line);
	return (shift_word_right_fl(line));
}
