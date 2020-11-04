/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 16:40:05 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 22:27:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			back_to_previous_dir(t_mns *mns)
{
	char *previous_dir;

	chdir(previous_dir = get_env_var(mns->envp, "OLD_PWD", 0));
	if (ft_strcmp(previous_dir, ""))
	{
		ft_putstr_fd(previous_dir, 1);
		ft_putstr_fd("\n", 1);
		free(previous_dir);
		return (1);
	}
	free(previous_dir);
	return (0);
}

int					set_pwd(t_mns *mns)
{
	char	actu_dir[MAX_CHAR_IN_PROMPT];
	char	*export_path[2];

	getcwd(actu_dir, sizeof(actu_dir));
	export_path[0] = ft_strdup("export");
	export_path[1] = ft_strjoin("PWD=", actu_dir);
	export_path[2] = NULL;
	b_export(mns, export_path);
	free(export_path[0]);
	free(export_path[1]);
	return (0);
}

static int			path_exist(t_mns *mns, char *old_path, char *path)
{
	char	actu_dir[MAX_CHAR_IN_PROMPT];

	if (!(ft_strcmp(path, "-")))
	{
		if ((back_to_previous_dir(mns)) < 0)
		{
			return (update_last_return(mns, display_error_tf(" cd: '", path,
			"' no such file or directory", 1)));
		}
		export_old_path(mns, old_path);
		set_pwd(mns);
		update_last_return(mns, 0);
		return (1);
	}
	else
	{
		if (!(getcwd(actu_dir, sizeof(actu_dir))))
			return (update_last_return(mns, 1));
	}
	return (update_last_return(mns, 0));
}

int					b_cd(t_mns *mns, char **tabl, int i_path)
{
	char	*path;
	char	old_path[MAX_CHAR_IN_PROMPT];

	if ((ft_tablen(tabl)) > 2)
		return (update_last_return(mns, display_error_tf("cd:", E_C, NULL, 1)));
	if (!(cd_use_multiple_args(tabl, i_path)))
	{
		update_last_return(mns, 2);
		return (display_error_tf("cd:", " Non valable option", NULL, 1));
	}
	if (tabl[i_path])
		path = tabl[i_path];
	else
		path = NULL;
	if (!(getcwd(old_path, sizeof(old_path))))
		display_warning_tf("cd:", " Directory deleted ",
		" cd - has been moved", 1);
	if (path)
	{
		if ((path_exist(mns, old_path, path)))
			return (TRUE);
	}
	return (check_path(mns, path, old_path));
}
