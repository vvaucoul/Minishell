/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:05:33 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/27 18:32:36 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Main export functions
*/

static int		place_env(t_mns *mns, char *line)
{
	T_BOOL	has_equal;
	T_BOOL	already_existing;
	char	*cmd;
	char	*value;

	has_equal = str_has_equal(line);
	cmd = get_export_cmd(line);
	value = get_export_value(line);
	already_existing = value_already_existing(mns->envp, cmd);
	if (!has_equal && !already_existing)
		return (0);
	set_envp_value(epur_b_str(cmd), epur_b_str(value), already_existing,
	&mns->envp);
	return (0);
}

int				b_export(t_mns *mns, char **tabl)
{
	int i;

	i = 0;
	tabl = remove_builtin_in_tab(tabl);
	while (tabl[i])
	{
		place_env(mns, tabl[i]);
		++i;
	}
	return (0);
}
