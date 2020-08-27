/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:30:05 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/27 18:40:31 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unset_remove(char *line, char **envp)
{
	int envp_line;

	envp_line = get_envp_line(line, envp);
	envp[envp_line] = NULL;
	return (0);
}

int		b_unset(char **tabl, char **envp)
{
	int i;

	i = 0;
	while (tabl[i])
	{
		unset_remove(tabl[i], envp);
		++i;
	}
	return (0);
}
