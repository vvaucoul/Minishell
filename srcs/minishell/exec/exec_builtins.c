/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:19:30 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/10 16:50:15 by vvaucoul         ###   ########.fr       */
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
		printf("test1\n");
		b_echo(command);
		// exit(0);
		printf("test2\n");
		return (1);
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
		printf("test1\n");
		b_export(mns, command);
		// exit(0);
		printf("test2\n");
		return (1);
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
