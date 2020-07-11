/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:14:43 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/10 19:54:06 by root             ###   ########.fr       */
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
			// printf("run path : [%s]\n", command[0]); //todo rm
			// return (1); //todo rm
			return (run(mns, command[0], command, mns->envp));
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
		// printf("{%s}\n", sysbin_loc[i]);
		if (ft_strstartswith(command[0], sysbin_loc[i], 0, 0))
			path = ft_strdup(command[0]);
		else
			path = ft_strjoin(sysbin_loc[i], command[0]);
		// printf("[%s]\n", path);
		if (lstat(path, &stat) == -1)
			free(path);
		else
		{
			ft_freetab(sysbin_loc);
			// printf("system command\n");
			return (is_exec(command, path, mns, stat));
		}
	}
	// printf("not a system command\n");
	ft_freetab(sysbin_loc);
	return (1);
}
