/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:02:09 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/01 16:02:02 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		b_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		++i;
	}
	return (0);
}
