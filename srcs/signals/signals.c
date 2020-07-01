/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:46:51 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/06/30 18:01:20 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		handle_signals(int signal)
{
    if (signal == SIGINT)
    printf("received SIGINT\n");
    else if (signal == SIGQUIT)
    printf("received SIGQUIT\n");
    else if (signal == SIGTERM)
    printf("received SIGTERM\n");

    return ;
}

int		init_signals_handle()
{
	//if (signal(SIGINT, handle_signals) == SIG_ERR)
	//printf("error, can't catch SIGINT\n");

	//if (signal(SIGQUIT, handle_signals) == SIG_ERR)
	//printf("error, can't catch SIGQUIT\n");

	//if (signal(SIGTERM, handle_signals) == SIG_ERR)
	//printf("error, can't catch SIGTERM\n");
    return (0);
}
