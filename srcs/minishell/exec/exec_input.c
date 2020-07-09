/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:43:39 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/09 18:43:44 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_input(char **commands, t_mns *mns)
{
	int ret;
	int i;

	ret = 0;
	i = 0;
	while (commands[i])
	{
		ret = exec_command(commands[i], mns);
		if (ret == -1)
			break ;
		i++;
	}
	return (ret);
}
