/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:12:33 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/03 16:03:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				get_input(t_mns *mns, char **input)
{
	char	buf;
	int		i;
	int		count;
	int		n_read;

	display_prompt(mns);
	if (!(*input = ft_strnew(1)))
		return (-1);
	count = 1;
	i = 0;
	while ((n_read = read(0, &buf, 1)) && buf != '\n')
	{
		*(*input + i++) = buf;
		if (!(*input = ft_realloc(*input, count + 1)))
			return (-1);
		count++;
	}
	if (!n_read)
	{
		free(*input);
		mns->use_ctrl_d = TRUE;
		return (0);
	}
	*(*input + i) = '\0';
	return (0);
}
