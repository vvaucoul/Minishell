/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:43:39 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/25 16:36:36 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		exec_command(char **command, t_mns *mns)
{
	int				ret;
	struct stat		stat;

	if ((ret = exec_pipes_redirections(command, mns)) > 0)
		return (ret);
	if ((ret = exec_builtins(command, mns)) != 1)
		return (ret);
	if (!ft_strchr(command[0], '/'))
	{
		if ((ret = exec_system(command, mns)) != 1)
			return (ret);
	}
	else if (exec_local_exec(command, mns) != 1)
		return (ret);
	if (lstat(command[0], &stat) != -1)
		if (stat.st_mode & S_IFDIR)
			return (b_cd(mns, command[0]) == -1); // check return
	display_error_cmd(command[0]);
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
		// print_table(command, "command");
		ret = exec_command(command, mns);
		// print_table(commands, "commands");
		// print_table(command, "command");
		// printf("ret = %d\n", ret);
		ft_freetab(command);
		if (ret == -1)
			break ;
		i++;
	}
	return (ret);
}
