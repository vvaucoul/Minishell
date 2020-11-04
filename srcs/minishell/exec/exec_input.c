/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:43:39 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 20:01:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Operators
** [1] = ";" [2] = "&&" ; [3] = "||"
*/

t_bool		check_operator(t_mns *mns, int ac_cmd)
{
	if (mns->operator.operator[ac_cmd] == 1)
		return (TRUE);
	else if (mns->operator.operator[ac_cmd] == 2)
	{
		if (!mns->last_return)
			return (TRUE);
		else
			return (FALSE);
	}
	else if (mns->operator.operator[ac_cmd] == 3)
	{
		if (mns->last_return)
			return (TRUE);
		else
			return (FALSE);
	}
	return (TRUE);
}

/*
** Exec commands
*/

int			exec_command(char **command, t_mns *mns)
{
	int				ret;
	struct stat		stat;

	if ((ret = exec_pipes_redirections(command, mns)))
		return ((ret == -1) ? 1 : 0);
	if ((ret = exec_builtins(command, mns)))
		return ((ret == -1) ? 1 : 0);
	if (!ft_strchr(command[0], '/'))
	{
		if ((ret = (check_specials_cmd(mns, command))))
			return ((ret == -1) ? 1 : 0);
		if ((ret = exec_system(command, mns)))
			return ((ret == -1) ? 1 : 0);
	}
	else if ((ret = exec_local_exec(command, mns)))
		return ((ret == -1) ? 1 : 0);
	if (lstat(command[0], &stat) != -1)
		if (stat.st_mode & S_IFDIR)
			return (b_cd(mns, command, 0) == 42);
	display_error_cmd(command[0]);
	update_last_return(mns, 127);
	return (0);
}

/*
** Called functions
*/

int			exec_input(char **commands, t_mns *mns)
{
	t_bool			can_do_cmd;
	char			**command;
	int				ret;
	int				i;

	ret = 0;
	i = 0;
	can_do_cmd = TRUE;
	while (commands[i])
	{
		if (update_input(&commands[i], mns))
			return (1);
		if (!(command = ultimate_quotesplit(commands[i])))
			return (1);
		if (can_do_cmd && command[0][0] != '\0')
			ret = exec_command(command, mns);
		can_do_cmd = TRUE;
		if (BONUS && !ret && !(check_operator(mns, i)))
			can_do_cmd = FALSE;
		ft_freetab(command);
		if (ret)
			return (ret);
		i++;
	}
	return (ft_freetab_ret(commands, ret));
}
