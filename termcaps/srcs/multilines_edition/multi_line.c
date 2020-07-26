/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:12:49 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/26 18:54:10 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static void display_prompt_line(int line)
{
	write(0, ft_itoa(line), ft_strlen(ft_itoa(line)));
	write(0, ">", 1);
}

static void update_cursor_position(t_size cp)
{
	tputs(tgoto(tgetstr("cm", NULL), cp.row, cp.col), 0, &term_putchar);
	// tputs(tgoto(tgetstr("cm", NULL), PROMPT_LEN + 1, line), 0, &term_putchar);
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

static t_line	**init_multilines(t_line *master)
{
	t_line		**ml_lines;
	int			i;
	int			j;

	ml_lines = (t_line **)malloc(sizeof(t_line *) * MAX_MULTI_LINE_ROW + 1);
	i = 0;
	while (i <= MAX_MULTI_LINE_ROW)
	{
		if (!(ml_lines[i] = malloc(sizeof(t_line))))
			return (NULL);
		ml_lines[i]->start.row = master->start.row + i;
		ml_lines[i]->start.col = master->start.col;
		ml_lines[i]->cursor_position = PROMPT_LEN;
		j = -1;
		while (j++ < MAX_LINE_LEN)
			ml_lines[i]->cmd[j] = '\0';
		//init_line_position(ml_lines[i]);
		++i;
	}
	return (ml_lines);
}

static int free_lines(t_line **ml_lines)
{
	int i;

	i = 0;
	while (i <= MAX_MULTI_LINE_ROW)
	{
		// cause crash, idk why
		//free(ml_lines[i]);
		++i;
	}
	//free(ml_lines);
	return (TRUE);
}

int		multi_line_manager(t_line *line, T_BOOL up, char key_pressed, T_BOOL reset)
{
	static	T_BOOL	init = FALSE;
	static	int		y = 0;
	static	int		start_y = 0;
	t_line			**ml_lines;

	// new system with one line per line

	// Init & Reset //
	if (!(init++))
	{
		ml_lines = init_multilines(line);
		y = line->start.row;
		start_y = y;
	}
	if (reset)
	{
		init = FALSE;
		convert_multilines_to_line(ml_lines, line);
		clear_multi_line_cmd(ml_lines);
		free_lines(ml_lines);
		return (FALSE);
	}

	// Manage Key with lines
	if (key_pressed != 0)
	{
		if (key_pressed >= 32 && key_pressed <= 126)
		{
			insert_char_in_line(ml_lines, start_y, y, key_pressed);

		}
		else if (key_pressed == 127)
		{
			delete_char_in_line(ml_lines, start_y, y, key_pressed);
		}

		return (TRUE);
	}

	// Move cursor [Up & Down]
	if (up)
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
	else if (y < start_y + MAX_MULTI_LINE_ROW)
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

	// old system with one line


	/*
	// autres touches peuvent rest, a faire
	if (reset)
	{
	convert_multilines_to_line(lines, line);
	clear_multi_line_cmd(line);
	reset_lines(line);
	init = FALSE;
	return (0);
}
if (!(init))
{
lines = init_multilines();
line->ml_position = line->start;
init = TRUE;
}


// clear line
if (line->ml_position.row != line->start.row)
{
tputs(tgoto(tgetstr("cm", NULL), 0, line->ml_position.row - 1), 0, &term_putchar);
}

if (up)
{
if (line->ml_position.row > line->start.row)
{
tputs(tgetstr("up", NULL), 0, &term_putchar);
--line->ml_position.row;
if (line->ml_position.row != line->start.row)
display_prompt_line(line->ml_position.row - line->start.row);
update_cursor_position(line);
}
}
else if ((line->ml_position.row - line->start.row) < MAX_MULTI_LINE_ROW)
{
tputs(tgetstr("do", NULL), 0, &term_putchar);
++line->ml_position.row;
display_prompt_line(line->ml_position.row - line->start.row);
update_cursor_position(line);
insert_nlc(line, 10);
}
else
update_cursor_position(line);
*/
return (0);
}
