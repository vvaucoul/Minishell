/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:43:13 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/11 22:00:42 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_command(char *line, t_mns *mns)
{
	char		**command;
	int			did_something;
	struct stat	stat;

	if (!(command = quotesplit(line, ' ')))
		return (-1);

	// free(line);

	if ((did_something = exec_builtins(command, mns)) != 1)
		return (did_something);
	if ((did_something = exec_system(command, mns)) != 1)
		return (did_something);
	if (lstat(command[0], &stat) != -1)
	{
		if (stat.st_mode & S_IFDIR)
			return (b_cd(mns, command[0]) == -1); // check return

			// ne pas executer les executable #windaows

		else if (stat.st_mode & S_IXUSR)
			return (exec(command, mns->envp)); // check return
	}
	display_error_cmd(command[0]);
	ft_freetab(command);
	return (0);
}
