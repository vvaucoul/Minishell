/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:29:17 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/04 15:46:50 by vvaucoul         ###   ########.fr       */
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
	if (!*use_multilines)
		*use_multilines = enable_multiline_manager(key_pressed);
	if (!*use_multilines)
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

	// move cursor left / right
	if (key_pressed == KEY_LEFT)
	multi_line_manager(line, 0, MLM_CM_LEFT);
	else if (key_pressed == KEY_RIGHT)
	multi_line_manager(line, 0, MLM_CM_RIGHT);

	// home & end
	if (key_pressed == KEY_HOME)
	multi_line_manager(line, 0, MLM_HOME);
	if (key_pressed == KEY_END)
	multi_line_manager(line, 0, MLM_END);

	// shift left right
	else if (key_pressed == KEY_SLEFT)
	multi_line_manager(line, 0, MLM_SW_LEFT);
	else if (key_pressed == KEY_SRIGHT)
	multi_line_manager(line, 0, MLM_SW_RIGHT);


	// end multiline edition
	if (key_pressed == '\n')
	{
		multi_line_manager(line, 0, MLM_RESET);
		add_in_history(line->cmd);
		history_manager(line, FALSE, TRUE);
		line->cursor_position = PROMPT_LEN;
		set_curpos(line);
		ft_putstr_fd(line->cmd, 0);
		printf("\ncmd line [%s]\n", line->cmd);
		*use_multilines = 2;
	}
	return (TRUE);
}
