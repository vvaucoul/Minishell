/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_pid_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:46:45 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 17:37:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** PID Functions
*/

int				pid_update(pid_t pid)
{
	get_spid()->global_pid = pid;
	return (pid);
}

pid_t			pid_getpid(void)
{
	return (get_spid()->global_pid);
}

/*
** State functions
*/

int				state_update(int state)
{
	return (get_spid()->mns_state = state);
}

int				state_getstate(void)
{
	return (get_spid()->mns_state);
}
