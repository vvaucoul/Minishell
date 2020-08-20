/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 17:00:07 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/06 17:26:33 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

void	clear_multi_line_cmd(int actu, int max)
{
	int sy;

	sy = actu;
	while (actu < max)
	{
		tputs(tgetstr("do", NULL), 0, &term_putchar);
		++actu;
	}
	actu = sy;
	while (max > actu)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, max - 1), 0, &term_putchar);
		tputs(tgetstr("ce", NULL), 0, &term_putchar);
		--max;
	}
}

void	init_convert_mltl(int *i1, int *i2)
{
	i1[0] = 0;
	i2[0] = 0;
}

void	convert_multilines_to_line(t_line **ml_lines, t_line *line)
{
	int i;
	int	j;
	int k;

	init_convert_mltl(&i, &j);
	while (i <= MAX_MULTI_LINE_ROW)
	{
		k = 0;
		while (ml_lines[i]->cmd[k])
		{
			line->cmd[j] = ml_lines[i]->cmd[k];
			++k;
			++j;
		}
		if (i + 1 < MAX_MULTI_LINE_ROW)
		{
			if (ft_strcmp(ml_lines[i + 1]->cmd, ""))
			{
				line->cmd[j] = ' ';
				++j;
			}
		}
		++i;
	}
	line->cmd[j] = '\0';
}

void	insert_char_in_line(t_line **ml_lines, int index, int key_pressed)
{
	if (ml_lines[index]->len + 1 >= MAX_LINE_LEN)
		return ;
	line_shift_right(ml_lines[index]);
	ml_lines[index]->cmd[ml_lines[index]->cursor_position - PROMPT_LEN] =
	key_pressed;
	++ml_lines[index]->len;
	++ml_lines[index]->cursor_position;
	tputs(tgetstr("im", NULL), 1, &term_putchar);
	write(0, &key_pressed, 1);
	tputs(tgetstr("ei", NULL), 1, &term_putchar);
}

void	delete_char_in_line(t_line **ml_lines, int index)
{
	cursor_to_left(ml_lines[index]);
	if (ml_lines[index]->cursor_position == ml_lines[index]->len + PROMPT_LEN)
		return ;
	line_shift_left(ml_lines[index]);
	--ml_lines[index]->len;
	tputs(tgetstr("ce", NULL), 0, &term_putchar);
	ft_putstr_fd(ml_lines[index]->cmd + (ml_lines[index]->cursor_position -
	PROMPT_LEN), 0);
	set_curpos(ml_lines[index]);
}
