/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 18:34:32 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/22 15:11:33 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		b_pwd(t_mns *mns, T_BOOL using_nl)
{
	char *dir;

	dir = get_env_var(mns->envp, "PWD", 0);
	ft_putstr_fd(dir, 1);
	if (using_nl)
		ft_putstr_fd("\n", 1);
	free(dir);
	return (0);
}
