/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 21:40:06 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 16:37:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	check_double_pipes(char **tabl)
{
	int		i;
	t_bool	is_pipe;

	i = 0;
	is_pipe = FALSE;
	while (tabl[i])
	{
		if (!(ft_strcmp(tabl[i], "|")) && is_pipe)
			return (1);
		if (!(ft_strcmp(tabl[i], "|")))
			is_pipe = TRUE;
		else
			is_pipe = FALSE;
		++i;
	}
	return (0);
}

static t_bool	check_first_pipe(char **tabl)
{
	if (!(ft_strcmp(tabl[0], "|")))
		return (1);
	return (0);
}

static t_bool	check_last_pipe(char **tabl)
{
	if (!(ft_strcmp(tabl[ft_tablen(tabl) - 1], "|")))
		return (1);
	return (0);
}

t_bool			pipes_valid(char **tabl)
{
	if (check_double_pipes(tabl))
		return (1);
	if (check_first_pipe(tabl))
		return (1);
	if (check_last_pipe(tabl))
		return (1);
	return (0);
}
