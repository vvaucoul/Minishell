/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 16:40:05 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/22 15:06:04 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			export_old_path(t_mns *mns, char *old_path)
{
	char	*export_path[2];

	export_path[0] = ft_strcat("OLD_PWD=", ft_strdup(old_path));
	export_path[1] = NULL;
	b_export(mns, export_path);
	return (0);
}

static		int back_to_previous_dir(t_mns *mns)
{
	chdir(get_env_var(mns->envp, "OLD_PWD", 0));
	return (0);
}

static	int		set_pwd(t_mns *mns)
{
	char	actu_dir[4096];
	char	*export_path[2];

	getcwd(actu_dir, sizeof(actu_dir));
	export_path[0] = ft_strcat("PWD=", ft_strdup(actu_dir));
	export_path[1] = NULL;
	b_export(mns, export_path);
	return (0);
}

static	int		change_dir(char *path, char *error)
{
	struct stat sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		if (chdir(path) < 0)
		{
			ft_putstr_fd(error, 1);
			return (0);
		}
	}
	else
	{
		ft_putstr_fd(error, 1);
		return (0);
	}
	return (0);
}

int				b_cd(t_mns *mns, char *path)
{
	char	old_path[4096];

	getcwd(old_path, sizeof(old_path));
	if (path)
	{
		if (!(ft_strcmp(path, "-")))
		{

			if (back_to_previous_dir(mns) < 0)
			{
				ft_putstr_fd(ft_strcat("cd: aucun dossier valide: ", ft_strcat(path, "\n")), 1);
				return (0);
			}
			export_old_path(mns, old_path);
			set_pwd(mns);
			return (0);
		}
	}
	if (!path)
	{

		if (change_dir(get_env_var(mns->envp, "HOME", 0), "cd: Home indefini\n") < 0)
		return (0);
		export_old_path(mns, old_path);
		set_pwd(mns);
	}
	else
	{

		if (change_dir(path, ft_strcat("cd: aucun dossier valide: ", ft_strcat(path, "\n"))) < 0)
		return (0);
		export_old_path(mns, old_path);
		set_pwd(mns);
	}
	return (0);
}
