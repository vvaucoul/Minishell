/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 16:40:05 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/01 16:34:38 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			export_old_path(t_mns *mns, char *old_path)
{
	char	*export_path[2];

	export_path[0] = ft_strcat("OLD_PWD=", ft_strdup(old_path));
	export_path[1] = NULL;
	printf(COLOR_RED); printf("export OLD_PWD = %s\n\n", export_path[0]); printf(COLOR_NOC);
	b_export(mns, export_path);
	return (0);
}

static		int back_to_previous_dir(t_mns *mns)
{
	char	*export_path[2];
	char	old_dir[4096];

	getcwd(old_dir, sizeof(old_dir));
	export_path[0] = ft_strcat("OLD_PWD=", ft_strdup(old_dir));
	export_path[1] = NULL;
	printf(COLOR_GREEN); printf("Go TO old pwd = %s\n\n", get_env_value("OLD_PWD", mns->envp)); printf(COLOR_NOC);
	if (chdir(get_env_value("OLD_PWD", mns->envp)) < 0)
	return (-1);
	printf(COLOR_RED); printf("export OLD_PWD = %s\n\n", export_path[0]); printf(COLOR_NOC);
	b_export(mns, export_path);
	return (0);
}

static	int		set_pwd(t_mns *mns)
{
	char	actu_dir[4096];
	char	*export_path[2];

	getcwd(actu_dir, sizeof(actu_dir));
	export_path[0] = ft_strcat("PWD=", ft_strdup(actu_dir));
	export_path[1] = NULL;
	printf(COLOR_RED); printf("export PWD = %s\n\n", export_path[0]); printf(COLOR_NOC);
	b_export(mns, export_path);
	return (0);
}

int				b_cd(t_mns *mns, char *path)
{
	char	old_path[4096];
	int pid;
	int state;

	printf("cd : %s\n", path);
	getcwd(old_path, sizeof(old_path));
	if (!(ft_strcmp(path, "-")))
	{
		printf(COLOR_YELLOW); printf("\t[1]\n"); printf(COLOR_NOC);
		back_to_previous_dir(mns);
		set_pwd(mns);
		return (0);
	}
	if (!path)
	{
		printf(COLOR_YELLOW); printf("\t[2]\n"); printf(COLOR_NOC);
		if (chdir(get_env_value("HOME", mns->envp)) < 0)
		{
			ft_putstr_fd("cd: Home indefini\n", 1);
			return (-1);
		}
		export_old_path(mns, old_path);
		set_pwd(mns);
	}
	else
	{
		printf(COLOR_YELLOW); printf("\t[3]\n"); printf(COLOR_NOC);
		if (chdir(path) < 0)
		{
			ft_putstr_fd("cd: aucun dossier valide\n", 1);
			return (-1);
		}
		export_old_path(mns, old_path);
		set_pwd(mns);
	}
	return (0);
}
