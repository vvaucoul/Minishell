/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:18:07 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/12 12:44:50 by root             ###   ########.fr       */
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

	mns = init_mns(envp, argc, argv);
	init_signals_handle();
	minishell(mns);
	free(mns);
	return (0);
}
