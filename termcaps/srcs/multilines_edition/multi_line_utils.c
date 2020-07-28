/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 17:00:07 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/28 17:53:59 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

void	ml_delete_char(t_line *line, int key_pressed)
{

}

void 	clear_multi_line_cmd(t_line *ml_lines, int actu, int max)
{
	int sy;


	// printf("actu [%d] | max [%d]\n", actu, max);
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

void 	convert_multilines_to_line(t_line **ml_lines, t_line *line)
{
	int i;
	int	j;
	int k;

	i = 0;
	j = 0;
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

void 	insert_char_in_line(t_line **ml_lines, int index, int key_pressed)
{
	if (ml_lines[index]->len + 1 >= MAX_LINE_LEN)
	return ;
	line_shift_right(ml_lines[index]);
	ml_lines[index]->cmd[ml_lines[index]->cursor_position - PROMPT_LEN] = key_pressed;
	++ml_lines[index]->len;
	++ml_lines[index]->cursor_position;

	printf("\nline cursor [%d]\n", ml_lines[index]->cursor_position);

	tputs(tgetstr("im", NULL), 1, &term_putchar);
	write(0, &key_pressed, 1);
	tputs(tgetstr("ei", NULL), 1, &term_putchar);
}

void 	delete_char_in_line(t_line **ml_lines, int index, int key_pressed)
{
	cursor_to_left(ml_lines[index]);
	if (ml_lines[index]->cursor_position == ml_lines[index]->len + PROMPT_LEN)
	return ;
	line_shift_left(ml_lines[index]);
	--ml_lines[index]->len;
	tputs(tgetstr("ce", NULL), 0, &term_putchar);
	ft_putstr_fd(ml_lines[index]->cmd + (ml_lines[index]->cursor_position - PROMPT_LEN), 0);
	set_curpos(ml_lines[index]);
}
