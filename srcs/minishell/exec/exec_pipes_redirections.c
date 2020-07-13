/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:39:16 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/13 18:30:12 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_pipes_redirections(char **command, t_mns *mns)
{
	if (tab_has_redirection(command))
	{
		main_redirections(command, mns->envp);
		return (1);
		printf("end redirections (not normal)\n");
	}
	if (tab_has_pipe(command))
	{
		p_pipe(command, mns->envp);
		return (1);
		printf("end pipes (not normal)\n");
	}
	return (0);
}