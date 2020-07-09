/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 18:34:32 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/09 19:07:26 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Builtin PWD
**	Affiche le chemin d'accès absolum
*/

int		b_pwd(t_mns *mns, T_BOOL using_nl)
{
	char *dir;

	dir = ft_strdup(get_env_value("PWD", mns->envp));
	ft_putstr_fd(dir, 1);
	if (using_nl)
	ft_putstr_fd("\n", 1);
	free(dir);
	return (0);
}
