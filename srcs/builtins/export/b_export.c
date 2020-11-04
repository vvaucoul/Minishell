/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:05:33 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 22:04:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Display error Called once
*/

int				export_errors(char *str)
{
	if (!str)
		return (-1);
	else
		return (display_error_tf("export: '", str,
	"' not a valid identifier", 1));
			return (0);
}

/*
** Init struct per tabs
*/

t_b_export		*init_struct_export(void)
{
	t_b_export	*export_s;

	if (!(export_s = malloc(sizeof(t_b_export))))
		return (display_error_tf("Malloc Error", NULL, NULL, -1) ? NULL : NULL);
	export_s->has_equal = FALSE;
	export_s->already_existing = FALSE;
	export_s->use_join = FALSE;
	ft_init_to_null(&export_s->cmd, &export_s->value, NULL, NULL);
	return (export_s);
}

int				free_struct_export(t_b_export *export_s)
{
	multi_free(export_s->cmd, export_s->value, NULL, NULL);
	free(export_s);
	return (0);
}

/*
** Main export func
*/

static int		export_loop(t_mns *mns, char *line, char **export_tabl)
{
	t_b_export	*export_s;
	int			ret;

	if (!(export_s = init_struct_export()))
		return (-1);
	if (init_struct_export_values(mns, export_s, line))
	{
		if ((check_export_warnings(export_s)))
		{
			if ((ret = export_set_env(mns, export_s)) == -1)
				return (display_error_tf("Malloc Error", NULL, NULL, -1));
		}
	}
	else
	{
		export_errors(line);
		free_struct_export(export_s);
		ft_freetab(export_tabl);
		update_last_return(mns, 1);
		return (1);
	}
	free_struct_export(export_s);
	return (FALSE);
}

int				b_export(t_mns *mns, char **tabl)
{
	char		**export_tabl;
	int			i;
	int			ret;

	update_last_return(mns, 0);
	if (ft_tablen(tabl) == 1 && ((!ft_strcmp(tabl[0], "export"))))
		return (b_export_display(mns));
	if (!(export_tabl = init_export_tabl(tabl)))
		return (display_error_tf("Malloc Error", NULL, NULL, -1));
	i = 0;
	while (export_tabl[i])
	{
		if ((ret = export_loop(mns, export_tabl[i], export_tabl)))
			return (ret);
		++i;
	}
	ft_freetab(export_tabl);
	return (1);
}
