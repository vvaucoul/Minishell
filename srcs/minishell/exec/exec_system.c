/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:14:43 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/04 11:53:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec(char **tabl, t_mns *mns)
{
	pid_update(fork());
	if (!pid_getpid())
		exit(execve(tabl[0], tabl, mns->envp));
	else if (pid_getpid() > 0)
		waitpid(pid_getpid(), &get_spid()->mns_state, 0);
	else
	{
		display_errno_error();
		return (0);
	}
	pid_update(0);
	update_last_return(mns, WEXITSTATUS(state_getstate()));
	if (WEXITSTATUS(state_getstate()) == 127)
		return (display_error_tf(tabl[0], ": command not found", NULL, 1));
	else if (WEXITSTATUS(state_getstate()) == 128)
		return (display_error_tf(tabl[0],
		": no such file or directory", NULL, 1));
	else if (WEXITSTATUS(state_getstate()) == 126)
		return (display_error_tf(tabl[0], ": permission denied", NULL, 1));
	state_update(WEXITSTATUS(state_getstate()));
	return (1);
}

int			is_exec(char **command, char *path, t_mns *mns, struct stat stat)
{
	if (stat.st_mode & S_IFREG)
	{
		if (stat.st_mode & S_IXUSR)
		{
			free(command[0]);
			command[0] = path;
			return (exec(command, mns));
		}
		display_error_tf("minishell: permission denied: ", path, NULL, 0);
	}
	free(path);
	return (1);
}

char		**get_sysbin_loc(char **envp)
{
	char	**sysbin_loc;
	char	*tmp;
	int		i;
	int		size;

	tmp = get_env_var(envp, "PATH", FALSE);
	if (!(sysbin_loc = ft_split(tmp, ':')))
		return (NULL);
	free(tmp);
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
		if (ft_strstartswith(command[0], sysbin_loc[i], FALSE, FALSE))
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
	update_last_return(mns, 127);
	display_error_tf(command[0], ": command not found", NULL, 1);
	return (ft_freetab_ret(sysbin_loc, 1));
}

int			exec_local_exec(char **command, t_mns *mns)
{
	char			*path;
	char			*tmp;
	struct stat		stat;
	char			*pwd;

	if ((cd_start_with_path(mns, command)))
		return (1);
	tmp = get_env_var(mns->envp, "PWD", 0);
	pwd = ft_straddchar(tmp, '/');
	if (ft_strstartswith(command[0], pwd, FALSE, FALSE) || command[0][0] == '/')
		path = ft_strdup(command[0]);
	else
		path = ft_strjoin(pwd, command[0]);
	free(pwd);
	if (lstat(path, &stat) == -1)
	{
		update_last_return(mns, 127);
		display_error_tf(command[0], ": command not found", NULL, 1);
		free(path);
	}
	else
		return (is_exec(command, path, mns, stat));
	return (1);
}
