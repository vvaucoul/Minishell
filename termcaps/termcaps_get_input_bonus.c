/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_get_input_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:53:01 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/15 18:34:24 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"


int			get_key(void)
{
	char	*key_str;
	int		key_pressed;

	key_str = ft_strnew(MAX_KEY_LEN);
	if (!key_str)
		return (-1);
	read(0, key_str, 1);
	if (*key_str == '\x1b')
		read(0, key_str + 1, MAX_KEY_LEN - 1);
	free(key_str);
	return (key_pressed);
}

int		termcaps_get_input(t_line *line, t_mns *mns)
{
	int		key_pressed;

	while (1)
	{
		key_pressed = get_key();
		printf("key_pressed = %d\n", key_pressed);
	}
	return (0);
}
