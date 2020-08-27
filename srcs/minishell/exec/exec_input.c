/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:43:39 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/27 17:01:59 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		exec_command(char **command, t_mns *mns)
{
	int				ret;
	struct stat		stat;

	if ((ret = exec_pipes_redirections(command, mns)) > 0)
		return ((mns->last_return = ret) == -1);
	if ((ret = exec_builtins(command, mns)) != 2)
		return ((mns->last_return = ret) == -1);
	if (!ft_strchr(command[0], '/'))
	{
		if ((ret = exec_system(command, mns)) != 1)
			return ((mns->last_return = ret) == -1);
	}
	else if (exec_local_exec(command, mns) != 1)
		return ((mns->last_return = ret) == -1);
	if (lstat(command[0], &stat) != -1)
			if (stat.st_mode & S_IFDIR)
				return ((mns->last_return = b_cd(mns, command[0])) == -1);
	display_error_cmd(command[0]);
	mns->last_return = 127;
	return (0);
}

int				exec_input(char **commands, t_mns *mns)
{
	char			**command;
	int				ret;
	int				i;

	ret = 0;
	i = 0;
	while (commands[i])
	{
		if (!(command = quotesplit(commands[i], ' ')))
			return (-1);
		ret = exec_command(command, mns);
		ft_freetab(command);
		if (ret == -1)
			break ;
		i++;
	}
	return (ret);
}
