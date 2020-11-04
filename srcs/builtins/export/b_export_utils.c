/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:03:16 by user42            #+#    #+#             */
/*   Updated: 2020/11/01 10:39:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool			export_use_join(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] && cmd[i] != ENV_DELIMITEUR)
	{
		if (cmd[i + 1])
		{
			if (cmd[i] == ENV_JOIN_DELIMITEUR && cmd[i + 1] == ENV_DELIMITEUR)
				return (TRUE);
		}
		++i;
	}
	return (FALSE);
}

/*
** Get ENVP line
*/

static int		ft_strdel(char *str, char del)
{
	int i;

	i = 0;
	while (str[i] && str[i] != del)
		++i;
	return (i);
}

int				get_envp_line(char *cmd, char **envp, char delimiteur)
{
	int i;

	i = 0;
	if (!(cmd))
		return (-1);
	while (envp[i])
	{
		if (!(ft_strncmp(cmd, envp[i], ft_strdel(cmd, delimiteur))))
			return (i);
		++i;
	}
	return (-1);
}

t_bool			str_has_equal(char *str)
{
	if (!(ft_strchr(str, ENV_DELIMITEUR)))
		return (FALSE);
	return (TRUE);
}

char			**init_export_tabl(char **tabl)
{
	char	**export_tabl;
	int		i;

	if (ft_tablen(tabl) <= 1)
		return (NULL);
	if (!(export_tabl = malloc(sizeof(char *) * ft_full_tablen(tabl))))
		return (NULL);
	i = 1;
	while (tabl[i])
	{
		if (!(export_tabl[i - 1] = ft_strdup(tabl[i])))
			return (NULL);
		++i;
	}
	export_tabl[i - 1] = NULL;
	return (export_tabl);
}
