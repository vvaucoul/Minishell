/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:10:38 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/27 18:32:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Does the string contain a '='
*/

T_BOOL		str_has_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ENV_DELIMITEUR)
			return (1);
		++i;
	}
	return (0);
}

/*
**	Get CMD & Value from line (toto=tata || toto= || toto)
*/

char		*get_export_cmd(char *line)
{
	return (ft_strtrunc_del(line, ENV_DELIMITEUR));
}

static int	export_value_start(int *i, int *j, int *si, char *str)
{
	i[0] = 0;
	j[0] = 0;
	if (!str)
		return (-1);
	while ((str[i[0]]) && (str[i[0]] != ENV_DELIMITEUR))
		++i[0];
	if (i[0] == (int)ft_strlen(str))
		return (-1);
	si[0] = i[0];
	while (str[i[0]])
		++i[0];
	return (0);
}

char		*get_export_value(char *str)
{
	char	*value;
	int		i;
	int		si;
	int		j;

	if (export_value_start(&i, &j, &si, str))
		return (NULL);
	if (!(value = malloc(sizeof(char) * ((i - si)))))
		return (NULL);
	while (str[si])
	{
		value[j] = str[si];
		++j;
		++si;
	}
	value[j] = '\0';
	if (j == 0)
		return (NULL);
	return (value);
}

/*
**	Tab envp functions
*/

int			get_envp_line(char *cmd, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!(ft_strncmp(cmd, envp[i], ft_strlen(cmd))))
			return (i);
		++i;
	}
	return (-1);
}
