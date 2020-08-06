/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlm_shift_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:22:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/06 17:57:04 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static t_bool	is_validchar(char c)
{
	return ((c >= 33 && c <= 126) ? TRUE : FALSE);
}

static void		swl_mlm(t_line **ml_lines, int index,
t_bool *is_in_word, int scp)
{
	if (ml_lines[index]->cursor_position != scp)
		is_in_word[0] = TRUE;
	if (!(is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position
		- PROMPT_LEN - 1])))
		is_in_word[0] = FALSE;
	if (!(is_in_word[0]))
	{
		while (!(
			is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position
			- PROMPT_LEN])) && ml_lines[index]->cursor_position > PROMPT_LEN)
			--ml_lines[index]->cursor_position;
		while (is_validchar(
			ml_lines[index]->cmd[ml_lines[index]->cursor_position - PROMPT_LEN])
			&& ml_lines[index]->cursor_position > PROMPT_LEN)
			--ml_lines[index]->cursor_position;
	}
	if (!(is_in_word[0]))
		++ml_lines[index]->cursor_position;
	else
		shift_word_left(ml_lines[index]);
}

int				mlm_shift_word_left(t_line **ml_lines, int index)
{
	t_bool	is_in_word;
	int		scp;

	is_in_word = FALSE;
	scp = ml_lines[index]->cursor_position;
	while (is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position
		- PROMPT_LEN]) && ml_lines[index]->cursor_position > PROMPT_LEN)
		--ml_lines[index]->cursor_position;
	swl_mlm(ml_lines, index, &is_in_word, scp);
	set_curpos(ml_lines[index]);
	return (0);
}

static void		swr_mlm(t_line **ml_lines, int index,
t_bool *is_in_word, int scp)
{
	if (ml_lines[index]->cursor_position != scp)
		is_in_word[0] = TRUE;
	if (!(is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position -
		PROMPT_LEN + 1])))
		is_in_word[0] = FALSE;
	if (!(is_in_word[0]))
	{
		while (!(
			is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position -
			PROMPT_LEN])) && ml_lines[index]->cursor_position
			< ml_lines[index]->len + PROMPT_LEN)
			++ml_lines[index]->cursor_position;
		while (
			is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position -
			PROMPT_LEN]) && ml_lines[index]->cursor_position <
			ml_lines[index]->len + PROMPT_LEN)
			++ml_lines[index]->cursor_position;
	}
	if (!(is_in_word[0]))
		--ml_lines[index]->cursor_position;
	else
		shift_word_right(ml_lines[index]);
}

int				mlm_shift_word_right(t_line **ml_lines, int index)
{
	t_bool	is_in_word;
	int		scp;

	is_in_word = FALSE;
	scp = ml_lines[index]->cursor_position;
	while (is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position -
	PROMPT_LEN]) && ml_lines[index]->cursor_position < ml_lines[index]->len +
	PROMPT_LEN)
		++ml_lines[index]->cursor_position;
	swr_mlm(ml_lines, index, &is_in_word, scp);
	while (is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position -
	PROMPT_LEN]) && ml_lines[index]->cursor_position < ml_lines[index]->len +
	PROMPT_LEN)
		--ml_lines[index]->cursor_position;
	++ml_lines[index]->cursor_position;
	set_curpos(ml_lines[index]);
	return (0);
}
