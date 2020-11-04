/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:02:09 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 20:05:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		b_env(t_mns *mns, char **tabl)
{
	int i;

	i = 0;
	if (ft_tablen(tabl) > 1)
	{
		return (update_last_return(mns, display_error_tf("Use env without \
		arguments", NULL, NULL, 0)));
	}
	while (mns->envp[i])
	{
		if (str_has_equal(mns->envp[i]))
		{
			ft_putstr_fd(mns->envp[i], 1);
			ft_putchar_fd('\n', 1);
		}
		++i;
	}
	update_last_return(mns, 0);
	return (1);
}
