/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 18:03:46 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 16:52:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		display_prompt(t_mns *mns)
{
	ft_putstr_fd(MNS_COLOR_GREEN, 2);
	ft_putstr_fd("", 2);
	b_pwd(mns, FALSE);
	ft_putstr_fd(MNS_COLOR_CYAN, 2);
	ft_putstr_fd(" ➜ ", 2);
	ft_putstr_fd(MNS_COLOR_NOC, 2);
}

int			mns_exit(char **input)
{
	write(2, "exit\n", 5);
	if (!(*input = ft_strdup("exit")))
		return (1);
	return (0);
}

int			minishell(t_mns *mns)
{
	char		*input;
	char		**commands;

	while (1)
	{
		if ((get_input(mns, &input)) == -1)
			return (-1);
		if (mns->use_ctrl_d)
			if (mns_exit(&input))
				return (-1);
		if (ft_strisempty(input) || is_in_quotes(input, ft_strlen(input)))
		{
			if (is_in_quotes(input, ft_strlen(input)))
				display_error("Please close your quotes");
			free(input);
			continue ;
		}
		if (!(commands = check_semicolon(&input, mns)))
			continue ;
		if (exec_input(commands, mns))
			return (-1);
		if (mns->exit.exit_shell)
			b_exit(mns, mns->use_ctrl_d ? FALSE : TRUE);
	}
	return (0);
}
