/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:23:36 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/01 10:35:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**assign_tab(t_mns *mns)
{
	char	**export_tabl;
	int		i;

	i = 0;
	if (!(export_tabl = malloc(sizeof(char *) * (ft_full_tablen(mns->envp)))))
		return (NULL);
	while (mns->envp[i])
	{
		export_tabl[i] = ft_strdup(mns->envp[i]);
		++i;
	}
	export_tabl[i] = NULL;
	return (export_tabl);
}

static char		**filter_export(t_mns *mns)
{
	char	**export_tabl;
	char	*tmp;
	int		i;

	i = 0;
	if (!(export_tabl = assign_tab(mns)))
		return (NULL);
	while (export_tabl[i])
	{
		if (export_tabl[i + 1])
			if (ft_strcmp(export_tabl[i], export_tabl[i + 1]) > 0)
			{
				tmp = export_tabl[i];
				export_tabl[i] = export_tabl[i + 1];
				export_tabl[i + 1] = tmp;
				i = -1;
			}
		++i;
	}
	return (export_tabl);
}

static void		display_export_cotes(char *str)
{
	int		i;
	t_bool	found_equal;

	i = 0;
	found_equal = FALSE;
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		if (str[i] == '=' && !found_equal)
		{
			found_equal = TRUE;
			ft_putchar_fd('"', 1);
		}
		++i;
	}
	if (str_has_equal(str))
		ft_putchar_fd('"', 1);
}

int				b_export_display(t_mns *mns)
{
	char	**export_tabl;
	int		i;

	i = 0;
	if (!(export_tabl = filter_export(mns)))
		return (-1);
	while (export_tabl[i])
	{
		ft_putstr_fd("declare -x ", 1);
		display_export_cotes(export_tabl[i]);
		ft_putstr_fd("\n", 1);
		++i;
	}
	ft_freetab(export_tabl);
	return (1);
}
