/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 16:40:05 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/01 17:56:11 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			export_old_path(t_mns *mns, char *old_path)
{
	char	*export_path[2];

	export_path[0] = ft_strcat("OLD_PWD=", ft_strdup(old_path));
	export_path[1] = NULL;
	// printf(COLOR_RED); printf("export OLD_PWD = %s\n\n", export_path[0]); printf(COLOR_NOC);
	b_export(mns, export_path);
	return (0);
}

static		int back_to_previous_dir(t_mns *mns)
{
	// printf(COLOR_GREEN); printf("Go TO old pwd = %s\n\n", get_env_value("OLD_PWD", mns->envp)); printf(COLOR_NOC);
	if (chdir(get_env_value("OLD_PWD", mns->envp)) < 0)
		return (-1);
	return (0);
}

static	int		set_pwd(t_mns *mns)
{
	char	actu_dir[4096];
	char	*export_path[2];

	getcwd(actu_dir, sizeof(actu_dir));
	export_path[0] = ft_strcat("PWD=", ft_strdup(actu_dir));
	export_path[1] = NULL;
	// printf(COLOR_YELLOW); printf("export PWD = %s\n\n", export_path[0]); printf(COLOR_NOC);
	b_export(mns, export_path);
	return (0);
}

static	int		change_dir(char *path, char *error)
{
	if (opendir(path) >= 0)
	{
		if (chdir(path) < 0)
		{
			ft_putstr_fd(error, 1);
			return (-1);
		}
	}
	else
	{
		ft_putstr_fd("cd: Can't access to this directory", 1);
		return (-1);
	}
	return (0);
}

int				b_cd(t_mns *mns, char *path)
{
	char	old_path[4096];
	int pid;
	int state;

	getcwd(old_path, sizeof(old_path));
	if (!(ft_strcmp(path, "-")))
	{
		// printf(COLOR_YELLOW); printf("\n  [1]\n"); printf(COLOR_NOC);
		if (back_to_previous_dir(mns) < 0)
		{
			ft_putstr_fd("cd: aucun dossier valide\n", 1);
			return (-1);
		}
		export_old_path(mns, old_path);
		set_pwd(mns);
		return (0);
	}
	if (!path)
	{
		// printf(COLOR_YELLOW); printf("\n  [2]\n"); printf(COLOR_NOC);
		if (change_dir(get_env_value("HOME", mns->envp), "cd: Home indefini\n") < 0)
			return (-1);
		export_old_path(mns, old_path);
		set_pwd(mns);
	}
	else
	{
		// printf(COLOR_YELLOW); printf("\n  [3]\n"); printf(COLOR_NOC);
		if (change_dir(path, "cd: aucun dossier valide\n") < 0)
			return (-1);
		export_old_path(mns, old_path);
		set_pwd(mns);
	}
	return (0);
}
