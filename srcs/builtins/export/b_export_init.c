/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:22:08 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 22:02:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**  DEBUG PRINTF
** //printf("\n\tEXPORT [%s]\n\n", line);
** //printf("\t use join = [%d]\n", export_s->use_join);
** //printf("\t has equal = [%d]\n", export_s->has_equal);
** //if (export_s->already_existing != -1)
** 	//printf("\t already_existing = [%d] [%s]\n", export_s->already_existing,
** mns->envp[export_s->already_existing]);
** //else
** 	//printf("\t already_existing = [-1] [NULL]\n");
**
** //if (export_s->cmd)
** 	//printf("\t CMD = [%s]\n", export_s->cmd);
** //else
** 	//printf("\t CMD = [NULL]\n");
** //if (export_s->value)
** 	//printf("\t VALUE = [%s]\n", export_s->value);
** //else
** 	//printf("\t VALUE = [NULL]\n");
*/

int		init_struct_export_values(t_mns *mns, t_b_export *export_s, char *line)
{
	int ret;

	export_s->use_join = export_use_join(line);
	export_s->has_equal = str_has_equal(line);
	export_s->already_existing = get_envp_line(line, mns->envp,
	export_s->use_join ? ENV_JOIN_DELIMITEUR : ENV_DELIMITEUR);
	if (!(get_export_values(export_s, line)))
		return (FALSE);
	if (!(ret = check_export_errors(export_s)))
		update_last_return(mns, 1);
	return (ret);
}
