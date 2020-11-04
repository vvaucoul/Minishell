/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_bonus_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 18:26:40 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/02 10:46:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	BONUS Redirection Utils
*/

char	*get_end_str(char **tabl)
{
	int i;

	i = 0;
	while (tabl[i])
	{
		if (!(ft_strcmp(tabl[i], "<<")))
		{
			if (tabl[i + 1])
				return (tabl[i + 1]);
			else
				return (NULL);
		}
		++i;
	}
	return (NULL);
}

char	*read_line(void)
{
	char	buff;
	char	line[MAX_CHAR_IN_PROMPT];
	int		i;

	i = 0;
	buff = 0;
	while (buff != '\n')
	{
		read(0, &buff, 1);
		ft_putchar_fd(buff, 0);
		if (buff != '\n')
		{
			line[i] = buff;
			++i;
		}
	}
	line[i] = '\0';
	return (ft_strdup(line));
}

int		get_tab_size(char **tabl)
{
	int mx;
	int x;
	int i;

	mx = 0;
	x = 0;
	i = 0;
	while (tabl[i])
	{
		x = ft_strlen(tabl[i]);
		if (x > mx)
			mx = x;
		++i;
	}
	return (i * mx);
}
