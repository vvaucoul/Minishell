/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 18:03:46 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/10 16:18:20 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void 	display_prompt(t_mns *mns)
{
	ft_putstr_fd(COLOR_GREEN, 1);
	b_pwd(mns, FALSE);
	ft_putstr_fd(COLOR_CYAN, 1);
	ft_putstr_fd(" ➜  ", 1);
	ft_putstr_fd(COLOR_NOC, 1);
}

int		minishell(t_mns *mns)
{
	char	*input;
	char	**commands;

	while (1)
	{
		display_prompt(mns);
		if ((get_input(&input, mns)) == -1)
			return (-1);
		if (ft_isemptystr(input, 1))
		{
			free(input);
			continue ;
		}
		commands = quotesplit(input, ';');
		free(input); //todo free in split :)
		if ((exec_input(commands, mns)) == -1)
			return (-1);
		ft_freetab(commands);
	}
	return (0);
}
