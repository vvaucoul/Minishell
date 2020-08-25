/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:12:33 by mle-faou          #+#    #+#             */
/*   Updated: 2020/08/21 15:58:31 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_input(char **input, t_mns *mns)
{
	char	buf;
	int		i;
	int		count;
	int		n_read;

	if (!(*input = ft_strnew(0)))
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
	*(*input + i) = '\0';
	if (!n_read)
	{
		free(*input);
		exit_shell();
	}
	if (update_input(input, mns))
		return (-1);
	return (0);
}
