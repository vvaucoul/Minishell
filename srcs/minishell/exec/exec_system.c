/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:14:43 by mle-faou          #+#    #+#             */
/*   Updated: 2020/08/27 16:33:24 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_exec(char **command, char *path, t_mns *mns, struct stat stat)
{
	if (stat.st_mode & S_IFREG)
	{
		if (stat.st_mode & S_IXUSR)
		{
			command[0] = path;
			printf("allo ?\n");
			return (exec(command, mns));
		}
		ft_putstr("minishell: permission denied: ");
		ft_putstr(path);
		ft_putstr("\n");
	}
	free(path);
	return (1);
}

char		**get_sysbin_loc(char **envp)
{
	char	**sysbin_loc;
	int		i;
	int		size;

	if (!(sysbin_loc = ft_split(get_env_var(envp, "PATH", 0), ':')))
		return (NULL);
	size = 0;
	while (sysbin_loc[size])
		size++;
	i = -1;
	while (++i < size)
		sysbin_loc[i] = ft_straddchar(sysbin_loc[i], '/');
	return (sysbin_loc);
}

int			exec_system(char **command, t_mns *mns)
{
	char			**sysbin_loc;
	int				i;
	char			*path;
	struct stat		stat;

	if (!(sysbin_loc = get_sysbin_loc(mns->envp)))
		return (-1);
	i = -1;
	while (sysbin_loc && sysbin_loc[++i])
	{
		if (ft_strstartswith(command[0], sysbin_loc[i], 0, 0))
			path = ft_strdup(command[0]);
		else
			path = ft_strjoin(sysbin_loc[i], command[0]);
		if (lstat(path, &stat) == -1)
			free(path);
		else
		{
			ft_freetab(sysbin_loc);
			return (is_exec(command, path, mns, stat));
		}
	}
	ft_freetab(sysbin_loc);
	return (1);
}

int			exec_local_exec(char **command, t_mns *mns)
{
	char			*path;
	struct stat		stat;
	char 			*pwd;

	pwd = ft_straddchar(get_env_var(mns->envp, "PWD", 0), '/');
	if (ft_strstartswith(command[0], pwd, 0, 0))
		path = ft_strdup(command[0]);
	else
		path = ft_strjoin(pwd, command[0]);
	if (lstat(path, &stat) == -1)
		free(path);
	else
	{
		free(pwd);
		return (is_exec(command, path, mns, stat));
	}
	free(pwd);
	return (1);
}
