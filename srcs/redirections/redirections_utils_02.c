/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils_02.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:02:03 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/10/26 21:35:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Utils
*/

int				find_first_redirection_pos(char **tabl)
{
	int i;

	i = 0;
	while (tabl[i])
	{
		if ((r_is_redirection(tabl[i])))
			return (i);
		++i;
	}
	return (FALSE);
}

int				count_redir(char **tabl)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (tabl[i])
	{
		if (r_is_redirection(tabl[i]))
			++nb;
		++i;
	}
	return (nb);
}

int				count_args(char **tabl)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (tabl[i])
	{
		if (!(r_is_redirection(tabl[i])))
			++nb;
		++i;
	}
	return (nb);
}

t_bool			last_arg_is_redirection(char **tabl)
{
	return (r_is_redirection(tabl[ft_tablen(tabl) - 1]));
}
