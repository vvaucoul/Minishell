/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:34:18 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/11 18:43:11 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		run_builtins(t_mns *mns, char *cmd, char **args, char **envp)
{
	int ret;

	ret = -1;
	if (!(ft_strcmp(cmd, "pwd")))
	ret = b_pwd(mns, TRUE);

	if (!(ft_strcmp(cmd, "cd")))
	ret = b_cd(mns, args[1]);

	if (!(ft_strcmp(cmd, "echo")))
	ret = b_echo(args);

	if (!(ft_strcmp(cmd, "export")))
	ret = b_export(mns, args);

	if (!(ft_strcmp(cmd, "unset")))
	ret = b_unset(args, envp);

	if (!(ft_strcmp(cmd, "env")))
	ret = b_env(mns);

	if (!(ft_strcmp(cmd, "exit")))
	ret = b_exit();

	return (ret);
}

int		run(t_mns *mns, char *cmd, char **args, char **envp)
{
	int		*contain_args;
	char	*tmp;

	contain_args = parse_arguments(args);
	tmp = args[0];
	args[0] = cmd;
	cmd = tmp;
	if (contain_args[1])
	{
		main_redirections(args, envp);
		return (0);
	}
	else if (contain_args[2])
	{
		p_pipe(args, envp);
		return (0);
	}
	if (contain_args[0])
		run_builtins(mns, cmd, args, envp);
	else if ((exec(args, envp)) < 0)
	{
		ft_putstr_fd("Error execution\n", 1);
		return (-1);
	}
	return (0);
}

int		exec(char **tab, char **envp)
{
	pid_t	pid;
	int	state;
	int ret;

	pid = fork();

	if (pid == 0)
	ret = execve(tab[0], tab, envp);
	else if (pid > 0)
	waitpid(pid, &state, WUNTRACED);
	else
	{
		ft_putstr_fd("Error fork", 1);
		return (-1);
	}
	return (1);
}
