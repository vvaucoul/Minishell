/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:32:36 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/04 10:42:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

int				termcaps_update_prompt_len(char *str,
	int size_to_add, t_bool to_free)
{
	int len;

	len = ft_strlen(str) + size_to_add;
	get_term_struct()->prompt_len = len;
	if (to_free)
		free(str);
	return (len);
}

static int		ft_intlen(int nb)
{
	int		len;

	len = 0;
	if (!nb)
		len++;
	while (nb)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

void			get_cursor_position(t_size *size)
{
	int		fc_i;
	int		i;
	char	buf[255];
	int		ret;

	fc_i = 0;
	i = 1;
	write(0, "\033[6n", 4);
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= 48 && buf[i] <= 57)
		{
			if (fc_i == 0)
				size->row = ft_atoi(&buf[i]) - 1;
			else
				size->col = ft_atoi(&buf[i]) - 1;
			++fc_i;
			i += ft_intlen(size->col) - 1;
		}
		++i;
	}
}
