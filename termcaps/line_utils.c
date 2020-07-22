/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:09:41 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/21 19:45:00 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

int		line_shift_right(t_line *line)
{
	int 	i;
	int		start;
	int		len;

	start = line->cursor_position - PROMPT_LEN - 1;
	len = strlen(line->cmd); //function
	while (len > start)
	{
		line->cmd[len + 1] = line->cmd[len];
		--len;
	}
	return (0);
}

int		line_shift_left(t_line *line)
{
	int 	i;
	int		start;
	int		len;

	start = line->cursor_position - PROMPT_LEN;
	len = strlen(line->cmd); //function
	while (start < len)
	{
		line->cmd[start] = line->cmd[start + 1];
		++start;
	}
	return (0);
}
