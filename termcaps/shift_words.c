/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:22:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/23 16:45:59 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static T_BOOL is_validchar(char c)
{
	return ((c >= 33 && c <= 126) ? TRUE : FALSE);
}

int		shift_word_left(t_line *line)
{
	T_BOOL is_in_word;
	int		scp;

	is_in_word = FALSE;
	scp = line->cursor_position;
	while (is_validchar(line->cmd[line->cursor_position - PROMPT_LEN]) && line->cursor_position > PROMPT_LEN)
	--line->cursor_position;
	if (line->cursor_position != scp)
	is_in_word = TRUE;
	if (!(is_validchar(line->cmd[line->cursor_position - PROMPT_LEN - 1])))
	is_in_word = FALSE;
	if (!(is_in_word))
	{
		while (!(is_validchar(line->cmd[line->cursor_position - PROMPT_LEN])) && line->cursor_position > PROMPT_LEN)
		--line->cursor_position;
		while (is_validchar(line->cmd[line->cursor_position - PROMPT_LEN]) && line->cursor_position > PROMPT_LEN)
		--line->cursor_position;
	}
	if (!(is_in_word))
	++line->cursor_position;
	else
	shift_word_left(line);
	set_curpos(line);
	return (0);
}

int		shift_word_right(t_line *line)
{
	T_BOOL is_in_word;
	int		scp;

	is_in_word = FALSE;
	scp = line->cursor_position;
	while (is_validchar(line->cmd[line->cursor_position - PROMPT_LEN]) && line->cursor_position < line->len + PROMPT_LEN)
		++line->cursor_position;
	if (line->cursor_position != scp)
		is_in_word = TRUE;
	if (!(is_validchar(line->cmd[line->cursor_position - PROMPT_LEN + 1])))
		is_in_word = FALSE;
	if (!(is_in_word))
	{
		while (!(is_validchar(line->cmd[line->cursor_position - PROMPT_LEN])) && line->cursor_position < line->len + PROMPT_LEN)
			++line->cursor_position;
		while (is_validchar(line->cmd[line->cursor_position - PROMPT_LEN]) && line->cursor_position < line->len + PROMPT_LEN)
			++line->cursor_position;
	}
	if (!(is_in_word))
		--line->cursor_position;
	else
	shift_word_right(line);
	while (is_validchar(line->cmd[line->cursor_position - PROMPT_LEN]) && line->cursor_position < line->len + PROMPT_LEN)
		--line->cursor_position;
	++line->cursor_position;
	set_curpos(line);
	return (0);
}
