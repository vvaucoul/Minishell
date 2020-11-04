/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:39:16 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/10/30 12:53:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_pipes_redirections(char **command, t_mns *mns)
{
	if (tab_has_pipe(command))
		return (p_pipe(mns, command));
	if (tab_has_redirection(command))
		return (main_redirections(mns, command));
	return (0);
}
