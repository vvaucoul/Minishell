/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:12:49 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/05 15:46:19 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static void display_prompt_line(int line)
{
	char *result;

	result = ft_itoa(line);
	write(0, result, ft_strlen(result));
	write(0, ">", 1);
	free(result);
}

static void update_cursor_position(t_size cp)
{
	tputs(tgoto(tgetstr("cm", NULL), cp.row, cp.col), 0, &term_putchar);
}

// static void reset_lines(t_line *line)
// {
// 	int i;
//
// 	i = 0;
// 	while (i <= MAX_MULTI_LINE_ROW)
// 	{
// 		tputs(tgoto(tgetstr("cm", NULL), 0, line->start.row + i), 0, &term_putchar);
// 		tputs(tgetstr("ce", NULL), 0, &term_putchar);
// 		++i;
// 	}
// 	tputs(tgoto(tgetstr("cm", NULL), 0, line->start.row), 0, &term_putchar);
// }
//
// static void insert_nlc(t_line *line, int key_pressed)
// {
// 	if ((line->len + 1) >= MAX_LINE_LEN)
// 	return ;
// 	line->cmd[line->cursor_position - PROMPT_LEN] = key_pressed;
// 	++line->len;
// 	line->cursor_position++;
// }
//
// void 	ml_refresh_lines(t_line *line)
// {
// 	int i;
//
// 	i = 0;
// 	clear_multi_line_cmd(line);
// 	while (i < line->ml_position.row - line->start.row)
// 	{
// 		display_prompt_line(line->ml_position.row - line->start.row);
// 		++i;
// 	}
// 	update_cursor_position(line);
// }

static int init_multilines(t_line **ml_lines, t_line *master)
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
		//	printf("ml_lines[%d] INIT\n", i);
		j = -1;
		while (j++ < MAX_LINE_LEN)
		ml_lines[i]->cmd[j] = '\0';
		//init_line_position(ml_lines[i]);
		++i;
	}
	if (ft_strcmp(master->cmd, ""))
	{
		free(ml_lines[0]);
		ml_lines[0] = master;
	}
	return (0);
}

static int free_lines(t_line *ml_lines, int max)
{
	int i;

	i = 0;
	while (i < max)
	{
		//free(ml_lines[i]);
		++i;
	}
	// free(ml_lines);
	return (TRUE);
}

int		multi_line_manager(t_line *line, char key_pressed, int state)
{
	static	T_BOOL	init = FALSE;
	static	int		y = 0;
	static	int		start_y = 0;
	static	t_line	*ml_lines;

	// new system with one line per line

	// Init & Reset //
	if (!(init++))
	{
		// printf("mlm INIT\n");
		init_multilines(&ml_lines, line);
		y = line->start.row;
		start_y = y;
	}
	if (state == MLM_RESET)
	{
		// printf("mlm RESET\n");
		init = FALSE;
		convert_multilines_to_line(&ml_lines, line);
		clear_multi_line_cmd(ml_lines, start_y, y);
		free_lines(ml_lines, y - start_y);
		return (FALSE);
	}

	// Manage Key with lines
	if (key_pressed != 0 && (state == MLM_ADD_KEY || state == MLM_REMOVE_KEY))
	{
		if (key_pressed >= 32 && key_pressed <= 126)
		insert_char_in_line(&ml_lines, y - start_y, key_pressed);
		else if (key_pressed == 127)
		delete_char_in_line(&ml_lines, y - start_y, key_pressed);
		return (TRUE);
	}

	// Multi line cursor motion
	if (state == MLM_CM_LEFT || state == MLM_CM_RIGHT || state == MLM_HOME || state == MLM_END)
	{
		if (state == MLM_CM_LEFT)
		ml_cm_left(&ml_lines, y - start_y);
		else if (state == MLM_CM_RIGHT)
		ml_cm_right(&ml_lines, y - start_y);

		if (state == MLM_HOME)
		ml_cm_start(&ml_lines, y - start_y);
		else if (state == MLM_END)
		ml_cm_end(&ml_lines, y - start_y);
		return (TRUE);
	}

	// Shift words
	if (state == MLM_SW_LEFT || state == MLM_SW_RIGHT)
	{
		if (state == MLM_SW_LEFT)
		mlm_shift_word_left(&ml_lines, y - start_y);
		if (state == MLM_SW_RIGHT)
		mlm_shift_word_right(&ml_lines, y - start_y);
		return (TRUE);
	}

	// Move cursor [Up & Down]
	if (state == MLM_UP)
	{
		if (y > start_y)
		{
			tputs(tgoto(tgetstr("cm", NULL), 0, y - 1), 0, &term_putchar);
			tputs(tgetstr("up", NULL), 0, &term_putchar);
			--y;
			if (y != start_y)
			display_prompt_line(y - start_y);
			update_cursor_position((t_size){PROMPT_LEN, y - 1});
		}
	}
	else if ((state == MLM_DOWN) && (y < start_y + MAX_MULTI_LINE_ROW))
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, y - 1), 0, &term_putchar);
		tputs(tgetstr("do", NULL), 0, &term_putchar);
		++y;
		display_prompt_line(y - start_y);
		update_cursor_position((t_size){PROMPT_LEN, y - 1});
	}
	else
	update_cursor_position((t_size){PROMPT_LEN, y - 1});
	return (TRUE);
}
