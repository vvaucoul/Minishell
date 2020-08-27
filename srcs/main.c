/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:18:07 by mle-faou          #+#    #+#             */
/*   Updated: 2020/08/27 18:37:39 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mns	*init_mns(char **envp, int argc, char **argv)
{
	t_mns	*mns;

	(void)argc;
	(void)argv;
	if (!(mns = malloc(sizeof(t_mns))))
		return (NULL);
	mns->envp = envp;
	mns->last_return = 0;
	return (mns);
}

int			main(int argc, char **argv, char **envp)
{
	t_mns	*mns;

	printf("test : %d\n", BONUS);

	if ((mns = init_mns(envp, argc, argv)) == NULL)
		return (-1);
	if (BONUS)
	{
		termcaps_init();
		term_get_info();
		termios_init();
	}
	// A reactiver pour le push final
	// init_signals_handle();
	minishell(mns);
	if (BONUS)
		termios_reset_term();
	free(mns);
	return (0);
}
