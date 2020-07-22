/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:12:33 by mle-faou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/07/22 14:45:26 by mle-faou         ###   ########.fr       */
=======
/*   Updated: 2020/07/21 17:15:29 by vvaucoul         ###   ########.fr       */
>>>>>>> d6737f7158fd90700f5143db6fd24d37968a0d3a
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
