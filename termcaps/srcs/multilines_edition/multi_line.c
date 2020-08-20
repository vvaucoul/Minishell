/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:12:49 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/06 17:21:46 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static int		init_multilines(t_line **ml_lines, t_line *master)
{
	int					i;
	int					j;

	i = 0;
	while (i <= MAX_MULTI_LINE_ROW)
	{
		if (!(ml_lines[i] = malloc(sizeof(t_line))))
			return (-1);
		ml_lines[i]->len = 0;
		ml_lines[i]->start.row = master->start.row + i;
		ml_lines[i]->start.col = master->start.col;
		ml_lines[i]->cursor_position = PROMPT_LEN;
		j = -1;
		while (j++ < MAX_LINE_LEN)
			ml_lines[i]->cmd[j] = '\0';
		++i;
	}
	if (ft_strcmp(master->cmd, ""))
	{
		free(ml_lines[0]);
		ml_lines[0] = master;
	}
	return (0);
}

static int		multi_line_manager_extended_ud(int state, int *y, int *start_y)
{
	if (state == MLM_UP)
	{
		if (y[0] > start_y[0])
		{
			tputs(tgoto(tgetstr("cm", NULL), 0, y[0] - 1), 0, &term_putchar);
			tputs(tgetstr("up", NULL), 0, &term_putchar);
			--y[0];
			if (y[0] != start_y[0])
				display_prompt_line(y[0] - start_y[0]);
			update_cursor_position((t_size){PROMPT_LEN, y[0] - 1});
		}
		return (1);
	}
	else if ((state == MLM_DOWN) && (y[0] < start_y[0] + MAX_MULTI_LINE_ROW))
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, y[0] - 1), 0, &term_putchar);
		tputs(tgetstr("do", NULL), 0, &term_putchar);
		++y[0];
		display_prompt_line(y[0] - start_y[0]);
		update_cursor_position((t_size){PROMPT_LEN, y[0] - 1});
		return (1);
	}
	return (0);
}

static int		multi_line_manager_extended_lr(int state, t_line **ml_lines,
int y, int start_y)
{
	if (state == MLM_CM_LEFT || state == MLM_CM_RIGHT || state == MLM_HOME ||
	state == MLM_END)
	{
		if (state == MLM_CM_LEFT)
			ml_cm_left(ml_lines, y - start_y);
		else if (state == MLM_CM_RIGHT)
			ml_cm_right(ml_lines, y - start_y);
		if (state == MLM_HOME)
			ml_cm_start(ml_lines, y - start_y);
		else if (state == MLM_END)
			ml_cm_end(ml_lines, y - start_y);
		return (TRUE);
	}
	if (state == MLM_SW_LEFT || state == MLM_SW_RIGHT)
	{
		if (state == MLM_SW_LEFT)
			mlm_shift_word_left(ml_lines, y - start_y);
		if (state == MLM_SW_RIGHT)
			mlm_shift_word_right(ml_lines, y - start_y);
		return (TRUE);
	}
	return (FALSE);
}

static int		multi_line_manager_extended_bi(t_line **ml_lines, int state,
int *y2, int key_pressed)
{
	if (key_pressed != 0 && (state == MLM_ADD_KEY || state == MLM_REMOVE_KEY))
	{
		if (key_pressed >= 32 && key_pressed <= 126)
			insert_char_in_line(ml_lines, y2[0] - y2[1], key_pressed);
		else if (key_pressed == 127)
			delete_char_in_line(ml_lines, y2[0] - y2[1]);
		return (TRUE);
	}
	return (FALSE);
}

int				multi_line_manager(t_line *line, char kp, int state)
{
	static	t_bool	init = FALSE;
	static	int		y = 0;
	static	int		start_y = 0;
	static	t_line	*ml;

	if (!(init++))
	{
		init_multilines(&ml, line);
		y = line->start.row;
		start_y = y;
	}
	if (state == MLM_RESET)
	{
		init = FALSE;
		convert_multilines_to_line(&ml, line);
		clear_multi_line_cmd(start_y, y);
		return (FALSE);
	}
	if (multi_line_manager_extended_bi(&ml, state, ((int[2]){y, start_y}), kp))
		return (TRUE);
	if (multi_line_manager_extended_lr(state, &ml, y, start_y))
		return (TRUE);
	if (!(multi_line_manager_extended_ud(state, &y, &start_y)))
		update_cursor_position((t_size){PROMPT_LEN, y - 1});
	return (TRUE);
}
