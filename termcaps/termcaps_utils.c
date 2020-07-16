/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:23:38 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/15 18:30:54 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

void	termcaps_get_cursor_start_pos(t_line *line)
{
	char	answer[ANSWER_LEN];
	int		i;

	ft_putstr_fd("\e[6n", 0);
	ft_bzero(answer, ANSWER_LEN);
	i = read(0, answer, ANSWER_LEN);
	answer[i] = 0;
	i = 2;
	line->start.row = ft_atoi(answer + i);
	while (ft_isdigit(answer[i]))
		i++;
	line->start.col = ft_atoi(answer + i + 1);
}
