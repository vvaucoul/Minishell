/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 18:10:14 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/06/29 18:16:31 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void 	disable_args(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

static t_mns	*init_struct(char **envp)
{
	t_mns	*mns;

	if (!(mns = malloc(sizeof(t_mns))))
		return (NULL);

	mns->is_running = TRUE;
	mns->envp = envp;
	return (mns);
}


int		main(int argc, char **argv, char **envp)
{
	t_mns	*mns;

	disable_args(argc, argv);

	if (!(mns = init_struct(envp)))
		return (-1);
	minishell(mns);
	free(mns);
	return (0);
}
