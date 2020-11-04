/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:38:46 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 19:56:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	CD Utils
*/

int					export_old_path(t_mns *mns, char *old_path)
{
	char	*export_path[2];

	export_path[0] = ft_strdup("export");
	export_path[1] = ft_strjoin("OLD_PWD=", old_path);
	export_path[2] = NULL;
	b_export(mns, export_path);
	free(export_path[0]);
	free(export_path[1]);
	return (0);
}

static int			change_dir(char *path, char *error)
{
	struct stat sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		if (chdir(path) < 0)
			return (display_error_tf(" cd: '", error, NULL, -1));
	}
	else
		return (display_error_tf("cd: ", error, NULL, -1));
	return (0);
}

int					check_path_export(t_mns *mns, char *old_path)
{
	export_old_path(mns, old_path);
	set_pwd(mns);
	return (0);
}

static int			check_path_exist(t_mns *mns, char *path, char *old_path)
{
	char *tmp;

	if ((cd_check_specials_paths(path)) < 0)
		return (1);
	if (change_dir(path, tmp = ft_strjoin(path,
	": no such file or directory")) < 0)
	{
		free(tmp);
		return (update_last_return(mns, 1));
	}
	free(tmp);
	check_path_export(mns, old_path);
	return (FALSE);
}

int					check_path(t_mns *mns, char *path, char *old_path)
{
	char	*tmp;

	if (!path)
	{
		if (change_dir(tmp = get_env_var(mns->envp, "HOME", 0),
		"Home indefini") < 0)
		{
			free(tmp);
			return (update_last_return(mns, 1));
		}
		free(tmp);
		check_path_export(mns, old_path);
	}
	else
	{
		if (check_path_exist(mns, path, old_path))
			return (1);
	}
	update_last_return(mns, 0);
	return (1);
}
