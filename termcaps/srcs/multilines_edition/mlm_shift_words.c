/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlm_shift_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:22:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/04 16:30:33 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static T_BOOL is_validchar(char c)
{
	return ((c >= 33 && c <= 126) ? TRUE : FALSE);
}

int		mlm_shift_word_left(t_line **ml_lines, int index)
{
	T_BOOL is_in_word;
	int		scp;

	is_in_word = FALSE;
	scp = ml_lines[index]->cursor_position;
	while (is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position - PROMPT_LEN]) && ml_lines[index]->cursor_position > PROMPT_LEN)
	--ml_lines[index]->cursor_position;
	if (ml_lines[index]->cursor_position != scp)
	is_in_word = TRUE;
	if (!(is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position - PROMPT_LEN - 1])))
	is_in_word = FALSE;
	if (!(is_in_word))
	{
		while (!(is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position - PROMPT_LEN])) && ml_lines[index]->cursor_position > PROMPT_LEN)
			--ml_lines[index]->cursor_position;
		while (is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position - PROMPT_LEN]) && ml_lines[index]->cursor_position > PROMPT_LEN)
			--ml_lines[index]->cursor_position;
	}
	if (!(is_in_word))
		++ml_lines[index]->cursor_position;
	else
		shift_word_left(ml_lines[index]);
	set_curpos(ml_lines[index]);
	return (0);
}

int		mlm_shift_word_right(t_line **ml_lines, int index)
{
	T_BOOL is_in_word;
	int		scp;

	is_in_word = FALSE;
	scp = ml_lines[index]->cursor_position;
	while (is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position - PROMPT_LEN]) && ml_lines[index]->cursor_position < ml_lines[index]->len + PROMPT_LEN)
		++ml_lines[index]->cursor_position;
	if (ml_lines[index]->cursor_position != scp)
		is_in_word = TRUE;
	if (!(is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position - PROMPT_LEN + 1])))
		is_in_word = FALSE;
	if (!(is_in_word))
	{
		while (!(is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position - PROMPT_LEN])) && ml_lines[index]->cursor_position < ml_lines[index]->len + PROMPT_LEN)
			++ml_lines[index]->cursor_position;
		while (is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position - PROMPT_LEN]) && ml_lines[index]->cursor_position < ml_lines[index]->len + PROMPT_LEN)
			++ml_lines[index]->cursor_position;
	}
	if (!(is_in_word))
		--ml_lines[index]->cursor_position;
	else
	shift_word_right(ml_lines[index]);
	while (is_validchar(ml_lines[index]->cmd[ml_lines[index]->cursor_position - PROMPT_LEN]) && ml_lines[index]->cursor_position < ml_lines[index]->len + PROMPT_LEN)
		--ml_lines[index]->cursor_position;
	++ml_lines[index]->cursor_position;
	set_curpos(ml_lines[index]);
	return (0);
}
