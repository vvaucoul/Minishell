/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:45:53 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 16:33:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*init_minishell_bonus(t_mns *mns, int *ret_read)
{
	char	*input;

	input = NULL;
	display_prompt(mns);
	termcaps_update_prompt_len(get_env_var(mns->envp, "PWD", FALSE), 3, TRUE);
	if ((*ret_read = term_read_line(&input)) == 2)
		mns->use_ctrl_d = TRUE;
	if (mns->use_ctrl_d)
	{
		free(input);
		write(2, "exit\n", 5);
		input = ft_strdup("exit");
	}
	return (input);
}

int			minishell_bonus(t_mns *mns)
{
	char		*input;
	char		**commands;
	int			ret_read;

	while (1)
	{
		input = init_minishell_bonus(mns, &ret_read);
		if (ft_strisempty(input) || is_in_quotes(input, ft_strlen(input)))
		{
			if (is_in_quotes(input, ft_strlen(input)))
				display_error("Please close your quotes");
			free(input);
			continue ;
		}
		remove_parenthesis(input);
		if (!(commands = check_semicolon(&input, mns)))
			continue ;
		if (!(commands = operatorsplit(mns, commands)))
			continue ;
		if (exec_input(commands, mns))
			return (-1);
		if (mns->exit.exit_shell)
			b_exit(mns, mns->use_ctrl_d ? FALSE : TRUE);
	}
	return (0);
}
