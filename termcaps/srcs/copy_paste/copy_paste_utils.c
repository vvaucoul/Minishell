/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 16:51:50 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/06 16:17:55 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

void		reset_copy_line(t_line *line)
{
	int i;

	i = -1;
	while (i <= MAX_LINE_LEN)
		line->copy_cmd[i++] = '\0';
}

void		insert_copy_character(t_line *line, int index, t_bool reset)
{
	static int i = 0;

	if (index >= MAX_LINE_LEN)
		return ;
	if (reset)
	{
		i = 0;
		return ;
	}
	line->copy_cmd[i] = line->cmd[index - get_term_struct()->prompt_len];
	line->copy_cmd[i + 1] = '\0';
	++i;
}

t_bool		index_valids(int *index)
{
	return ((index[0] > 0 && index[1] > 0) ? TRUE : FALSE);
}

void		swap_index(int **index)
{
	int tmp;

	if (index[0][0] > index[0][1])
	{
		tmp = index[0][0];
		index[0][0] = index[0][1];
		index[0][1] = tmp;
	}
}
