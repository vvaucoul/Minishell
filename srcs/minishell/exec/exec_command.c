/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:43:13 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/10 19:52:23 by root             ###   ########.fr       */
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

	// int i = 0;
	// while (command[i])
	// {
	// 	printf("~ command[%d] : [%s]\n", i, command[i]);
	// 	i++;
	// }
	// printf("test???????????\n");

	if ((did_something = exec_builtins(command, mns)) != 1)
		return (did_something);
	if ((did_something = exec_system(command, mns)) != 1)
		return (did_something);
	if (lstat(command[0], &stat) != -1)
	{
		if (stat.st_mode & S_IFDIR)
		{
			// printf("return (b_cd(command, mns) == -1);\n"); //todo rm
			return (b_cd(mns, command[0]) == -1); // check return
		}
		else if (stat.st_mode & S_IXUSR)
		{
			// printf("return (todo run fonction vv);\n"); //todo rm
			return (run(mns, command[0], command, mns->envp)); // check return
		}
	}
	ft_putstr("minishell: command not found: ");
	ft_putstr(command[0]);
	write(1, "\n", 1);
	ft_freetab(command);
	return (0);
}
