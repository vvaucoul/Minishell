/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_specials_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:23:34 by user42            #+#    #+#             */
/*   Updated: 2020/11/01 19:29:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_specials_cmd(t_mns *mns, char **tabl)
{
	if ((!ft_strcmp(tabl[0], ".")))
	{
		update_last_return(mns, 2);
		display_error_tf(tabl[0], ": command not found", NULL, 1);
		return (1);
	}
	else if ((!ft_strcmp(tabl[0], "..")))
	{
		update_last_return(mns, 127);
		display_error_tf(tabl[0], ": command not found", NULL, 1);
		return (1);
	}
	return (0);
}
