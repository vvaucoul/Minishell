/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:18:07 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/03 22:40:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mns	*init_mns(int argc, char **argv)
{
	t_mns	*mns;

	(void)argc;
	(void)argv;
	if (!(mns = malloc(sizeof(t_mns))))
		return (NULL);
	update_last_return(mns, 0);
	mns->use_ctrl_d = FALSE;
	return (mns);
}

int				main(int argc, char **argv, char **envp)
{
	t_mns	*mns;

	if ((mns = init_mns(argc, argv)) == NULL)
		return (-1);
	if (BONUS)
	{
		termcaps_init();
		term_get_info();
		termios_init();
	}
	init_signals_handle(mns);
	if (start_minishell(mns, envp) < 0)
	{
		display_malloc_error();
		return (-1);
	}
	if (!BONUS)
		minishell(mns);
	if (BONUS)
		minishell_bonus(mns);
	if (BONUS)
		termios_reset_term();
	free(mns);
	return (0);
}
