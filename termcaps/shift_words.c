/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 19:22:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/22 20:27:39 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static T_BOOL is_validchar(char c)
{
	return ((c >= 33 && c <= 126) ? TRUE : FALSE);
}

int		shift_word_left(t_line *line)
{
	// a finir, bien buggé !

	// start sur un character pris en compte (mais pas l espace)
	if (is_validchar(line->cmd[line->cursor_position]))
	{
		while (is_validchar(line->cmd[line->cursor_position]) && line->cursor_position - PROMPT_LEN > 0)
		{
			cursor_to_left(line);
			//printf("line->cursor_position - PROMPT_LEN = %d\n",line->cursor_position - PROMPT_LEN );
		}
		cursor_to_left(line);
	}
	// start sur un espace ou charactere non pris en compte
	else
	{
		while (!(is_validchar(line->cmd[line->cursor_position])))
		{
			cursor_to_left(line);
		}
	}
	cursor_to_right(line);
	return (0);
}

int		shift_word_right(t_line *line)
{

	return (0);
}
