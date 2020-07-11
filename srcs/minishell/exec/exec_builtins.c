/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:19:30 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/11 20:35:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_builtins(char **command, t_mns *mns)
{
	int i; //todo rm
	if (ft_strequ(command[0], "echo")) // n'ecrit rien
	{
		// printf("return (b_echo(command, mns));\n"); //todo rm
		// return (1); //todo rm
		i = 0;
		while (command[i])
		{
			// printf("echo commande[%d] : [%s]\n", i, command[i]);
			i++;
		}
		return (b_echo(command));
	}
	if (ft_strequ(command[0], "cd")) // crash
	{
		// printf("return (b_cd(command, mns));\n"); //todo rm
		// return (1); //todo rm
		//printf("command[1] : [%s]\n", command[1]);
		return (b_cd(mns, command[1]));
	}
	if (ft_strequ(command[0], "pwd")) // crash
	{
		// printf("return (b_pwd(command, mns));\n"); //todo rm
		// return (1); //todo rm
		return (b_pwd(mns, 1));
	}
	if (ft_strequ(command[0], "export")) // okay fuite de couleur
	{
		// printf("return (b_export(command, mns));\n"); //todo rm
		// return (1); //todo rm
		i = 0;
		while (command[i])
		{
			//printf("command[%d] : [%s]\n", i, command[i]);
			i++;
		}
		// exit(0);
		return (b_export(mns, command));
	}
	if (ft_strequ(command[0], "unset")) // okay fuite de couleur
	{
		// printf("return (b_unset(command, mns));\n"); //todo rm
		// return (1); //todo rm
		i = 0;
		while (command[i])
		{
			//printf("command[%d] : [%s]\n", i, command[i]);
			i++;
		}
		return (b_unset(command, mns->envp));
	}
	if (ft_strequ(command[0], "env")) // okay
	{
		// printf("return (b_env(command, mns));\n"); //todo rm
		// return (1); //todo rm
		return (b_env(mns));
	}
	if (ft_strequ(command[0], "exit")) //okay
	{
		// printf("return (b_exit(command, mns));\n"); //todo rm
		// return (1); //todo rm
		return (b_exit());
	}
	return (1);
}
