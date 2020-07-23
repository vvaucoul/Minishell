/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 19:12:49 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/23 19:36:32 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static void display_prompt_line(int line)
{
	write(0, ft_itoa(line), ft_strlen(ft_itoa(line)));
	write(0, ">", 1);
}

static void init_col_cursor(t_line *line)
{
	int i;

	i = 0;
	line->ml_position.col = PROMPT_LEN ;
	tputs(tgoto(tgetstr("cm", NULL), line->ml_position.col, line->ml_position.row - 1), 0, &term_putchar);
}

// a finir !

int		multi_line_manager(t_line *line, T_BOOL up, T_BOOL reset)
{
	static T_BOOL init = FALSE;

	// autres touches peuvent rest, a faire
	if (reset)
	init = FALSE;
	if (!(init))
	{
		line->ml_position = line->start;
		init = TRUE;
	}

	// clear line
	if (line->ml_position.row != line->start.row)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, line->ml_position.row - 1), 0, &term_putchar);
		//tputs(tgetstr("cb", NULL), 0, &term_putchar);
	}
	if (up)
	{
		if (line->ml_position.row > line->start.row)
		{
			tputs(tgetstr("up", NULL), 0, &term_putchar);
			--line->ml_position.row;
			if (line->ml_position.row != line->start.row)
				display_prompt_line(line->ml_position.row - line->start.row);
			init_col_cursor(line);
		}
	}
	else
	{
		tputs(tgetstr("do", NULL), 0, &term_putchar);
		++line->ml_position.row;
		if (line->ml_position.row != line->start.row)
			display_prompt_line(line->ml_position.row - line->start.row);
		init_col_cursor(line);
	}
}
