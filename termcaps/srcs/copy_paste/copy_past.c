/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_past.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:49:32 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/26 18:38:13 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

static void 	copy_line(t_line *line, int *index)
{
	insert_copy_character(line, 0, TRUE);
	swap_index(&index);
	while (index[0] <= index[1])
	{
		insert_copy_character(line, index[0], FALSE);
		++index[0];
	}
}

static void 	cut_line(t_line *line, int *index)
{
	int si[2];

	si[0] = index[0];
	si[1] = index[1];
	copy_line(line, index);
	index[0] = si[0];
	index[1] = si[1] + 1;
	swap_index(&index);
	line->cursor_position = index[1];
	set_curpos(line);

	while (index[1] >= index[0])
	{
		delete_char(line, 127);
		--index[1];
	}
	delete_char(line, 127);
}

static void 	paste_line(t_line *line, int *index)
{
	int i;

	i = 0;
	(void)index;
	while (line->copy_cmd[i])
	{
		insert_char(line, line->copy_cmd[i]);
		++i;
	}
}

void 	copy_paste_manager(t_line *line, T_BOOL set_index, int mode)
{
	static void 	(*pf[])(t_line *, int *) = {copy_line, cut_line, paste_line};
	static int		index[2] = {-1, -1};
	static T_BOOL	ac_index = 0;

	if (set_index && line->copy_cmd[0] == 0)
	{
		index[ac_index] = line->cursor_position;
		++ac_index;
		if (ac_index > 1)
		{
			ac_index = 0;
		}
		return ;
	}
	else if (index_valids(index))
	{
		pf[mode](line, index);
		if (mode == 2)
		{
			index[0] = -1;
			index[1] = -1;
			ac_index = 0;
			reset_copy_line(line);
		}
	}
}
