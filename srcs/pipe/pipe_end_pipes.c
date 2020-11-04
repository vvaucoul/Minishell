/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_end_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:37:43 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 16:37:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Free pipes
*/

int						free_pipes(t_pipe *pipe)
{
	int i;

	i = 0;
	while (i <= pipe->nb_pipe)
	{
		ft_freetab(pipe->pipe_tab[i]);
		++i;
	}
	free(pipe->pipe_tab);
	free(pipe->ac_pipes);
	return (TRUE);
}
