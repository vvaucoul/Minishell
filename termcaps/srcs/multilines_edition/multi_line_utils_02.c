/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line_utils_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:20:38 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/06 17:21:31 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

void		display_prompt_line(int line)
{
	char *result;

	result = ft_itoa(line);
	write(0, result, ft_strlen(result));
	write(0, ">", 1);
	free(result);
}

void		update_cursor_position(t_size cp)
{
	tputs(tgoto(tgetstr("cm", NULL), cp.row, cp.col), 0, &term_putchar);
}
