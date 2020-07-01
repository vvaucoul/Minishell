/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 18:24:23 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/06/29 18:34:29 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_home_line(char *str)
{
	char *line;
	int i;
	int si;

	i = 0;
	while (str[i] != '=')
		++i;
	si = ++i;
	while (str[i])
		++i;
	if (!(line = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		line[i] = str[si];
		++i;
		++si;
	}
	line[i] = '\0';
	return (line);
}

char			*get_env_value(char *value, char **envp)
{
	int j;

	j = 0;
	if (!value)
		return (NULL);
	while (envp[j])
	{
		if (!(ft_strncmp(envp[j], value, 3)))
			return (get_home_line(envp[j]));
		++j;
	}
	return (NULL);
}
