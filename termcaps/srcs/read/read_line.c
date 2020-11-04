/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:25:51 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/04 10:41:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

int		term_read_line(char **input)
{
	t_line	*line;
	int		key_pressed;
	int		ret;

	line = init_new_line();
	while (1)
	{
		key_pressed = get_key();
		if (!(ret = cmp_keys(line, key_pressed)) || (ret == 2))
			break ;
	}
	*input = ft_strdup(line->cmd);
	ft_putstr_fd("\n", 1);
	return (ret);
}
