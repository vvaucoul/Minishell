/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 18:34:32 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/01 16:19:16 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		b_pwd(char **envp, T_BOOL using_nl)
{
	//char dir[4096];
	char *dir;

	getcwd(dir, sizeof(dir));

	dir = ft_strdup(get_env_value("PWD", envp));

	ft_putstr_fd(dir, 1);
	if (using_nl)
	ft_putstr_fd("\n", 1);
	return (0);
}
