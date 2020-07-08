/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 18:24:23 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/01 17:44:10 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_cmd_line(char *str)
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

static	T_BOOL	strdelcmnp(char *s1, char *s2, char del)
{
	int	i;

	i = 0;
	//printf("compare : %s with %s\n", s1, s2);
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
	{
		if (s1[i] == del || s2[i] == del)
			return (0);
		++i;
	}
	return (s1[i] - s2[i]);
}

char			*get_env_value(char *value, char **envp)
{
	int j;

	j = 0;
	if (!value)
	return (NULL);
	while (envp[j])
	{
		if (!(strdelcmnp(envp[j], ft_strcat(value, "="), '=')))
			return (get_cmd_line(envp[j]));
		++j;
	}
	return (NULL);
}
