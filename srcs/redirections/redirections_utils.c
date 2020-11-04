/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:40:16 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/10/20 18:18:48 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	REDIRECTIONS
*/

int		r_get_redirection_type(char *str)
{
	if (!(ft_strcmp(str, ">")))
		return (1);
	else if (!(ft_strcmp(str, ">>")))
		return (2);
	else if (!(ft_strcmp(str, "<")))
		return (3);
	else if ((!(ft_strcmp(str, "<<"))) && BONUS)
		return (4);
	return (FALSE);
}

t_bool	r_is_redirection(char *str)
{
	if (!(ft_strcmp(str, ">")))
		return (TRUE);
	else if (!(ft_strcmp(str, ">>")))
		return (TRUE);
	else if (!(ft_strcmp(str, "<")))
		return (TRUE);
	else if ((!(ft_strcmp(str, "<<"))) && BONUS)
		return (TRUE);
	return (FALSE);
}

t_bool	r_is_pipe(char *str)
{
	return ((ft_strcmp(str, "|") == 0) ? TRUE : FALSE);
}

int		check_signal(int state)
{
	if (WTERMSIG(state) == 3)
		display_error("segfault (core dumped)\n");
	return (0);
}
