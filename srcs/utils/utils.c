/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 18:08:24 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/01 18:16:41 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_cmd_in_path(char *path)
{
	char *cmd;
	int i;
	int j;
	int k;

	i = ft_strlen(path);
	j = i;
	k = 0;
	while (path[i] != 47 && i > 0)
		--i;
	++i;
	if (!(cmd = malloc(sizeof(char) * (j - i) + 1)))
		return (NULL);
	while (i < j)
	{
		cmd[k] = path[i];
		++i;
		++k;
	}
	cmd[k] = '\0';
	return (cmd);
}
