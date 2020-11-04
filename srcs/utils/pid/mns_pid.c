/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 22:37:15 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 17:38:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Minishell PID & State
*/

/*
** Get PID struct
*/

static void		init_pid(t_pid *pid)
{
	pid->global_pid = 0;
	pid->mns_state = 0;
}

t_pid			*get_spid(void)
{
	static t_pid	pid;
	static t_bool	init = FALSE;

	if (!(init))
	{
		init_pid(&pid);
		init = TRUE;
	}
	return (&pid);
}
