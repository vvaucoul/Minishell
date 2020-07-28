/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:29:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/28 17:59:16 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static T_BOOL	enable_multiline_manager(int key_pressed)
{
	if (key_pressed == KEY_SHIFT_UP || key_pressed == KEY_SHIFT_DOWN)
		return (TRUE);
	return (FALSE);
}

int 	term_get_multiline(t_line *line, T_BOOL *use_multilines, int key_pressed)
{
	if (!use_multilines)
		*use_multilines = enable_multiline_manager(key_pressed);
	if (!use_multilines)
		return (FALSE);
	/*
	if (!(*use_multilines = enable_multiline_manager(key_pressed)))
	return (FALSE);
	*/

	// multi_line

	// basic input
	if (key_pressed >= 32 && key_pressed <= 126)
	multi_line_manager(line, key_pressed, MLM_ADD_KEY);
	else if (key_pressed == KEY_DC || key_pressed == 127)
	multi_line_manager(line, key_pressed, MLM_REMOVE_KEY);

	if (key_pressed == KEY_SHIFT_UP)
	multi_line_manager(line, 0, MLM_UP);
	else if (key_pressed == KEY_SHIFT_DOWN)
	multi_line_manager(line, 0, MLM_DOWN);

	if (key_pressed == KEY_LEFT)
	multi_line_manager(line, 0, MLM_CM_LEFT);
	else if (key_pressed == KEY_RIGHT)
	multi_line_manager(line, 0, MLM_CM_RIGHT);

	return (TRUE);
}
