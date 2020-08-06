/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:26:08 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/06 16:46:24 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

int		history_init(int reset, int *init, int up_down, t_history *hist)
{
	if (reset)
	{
		init[0] = 0;
		return (0);
	}
	if (!(init[0])++)
	{
		hist->hist_len = get_last_history_line();
		hist->actu_hist_line = hist->hist_len;
	}
	if (up_down)
	{
		if (hist->actu_hist_line > 0)
			--hist->actu_hist_line;
	}
	else
	{
		if (hist->actu_hist_line < hist->hist_len)
			++hist->actu_hist_line;
	}
	return (1);
}
