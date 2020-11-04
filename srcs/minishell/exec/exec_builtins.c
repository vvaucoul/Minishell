/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:19:30 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/02 00:51:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_builtins(char **command, t_mns *mns)
{
	if (ft_strequ(command[0], "echo"))
		return (b_echo(mns, command));
	if (ft_strequ(command[0], "cd"))
		return (b_cd(mns, command, 1));
	if (ft_strequ(command[0], "pwd"))
		return (b_pwd(mns, TRUE));
	if (ft_strequ(command[0], "export"))
		return (b_export(mns, command));
	if (ft_strequ(command[0], "unset"))
		return (b_unset(mns, command, mns->envp));
	if (ft_strequ(command[0], "env"))
		return (b_env(mns, command));
	if (ft_strequ(command[0], "exit"))
		return (init_exit_struct(mns, command));
	return (0);
}
