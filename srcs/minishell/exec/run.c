/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:34:18 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/27 18:22:21 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		run_builtins(t_mns *mns, char *cmd, char **args)
{
	int ret;

	ret = 0;
	if (!(ft_strcmp(cmd, "pwd")))
	ret = b_pwd(mns, TRUE);
	if (!(ft_strcmp(cmd, "cd")))
	ret = b_cd(mns, args[1]);
	if (!(ft_strcmp(cmd, "echo")))
	ret = b_echo(args);
	if (!(ft_strcmp(cmd, "export")))
	ret = b_export(mns, args);
	if (!(ft_strcmp(cmd, "unset")))
	ret = b_unset(args, mns->envp);
	if (!(ft_strcmp(cmd, "env")))
	ret = b_env(mns);
	if (!(ft_strcmp(cmd, "exit")))
	ret = b_exit(mns);
	return (ret);
}

int		run(t_mns *mns, char *cmd, char **args)
{
	int		*contain_args;
	char	*tmp;

	contain_args = parse_arguments(args);
	tmp = args[0];
	args[0] = cmd;
	cmd = tmp;
	if (contain_args[1])
	{
		main_redirections(args, mns->envp);
		return (0);
	}
	else if (contain_args[2])
	{
		p_pipe(args, mns->envp);
		return (0);
	}
	if (contain_args[0])
		run_builtins(mns, cmd, args);
	else if ((exec(args, mns)) < 0)
	{
		ft_putstr_fd("Error execution\n", 1);
		return (-1);
	}
	return (0);
}

int		run_cmd(t_mns *mns, char *cmd, char **tabl)
{
	pid_t	pid;
	int	state;

	pid = fork();
	if (!pid)
	{
		if (b_isvalid(tabl[0]))
			return (run_builtins(mns, cmd, tabl));
		else
			return(execve(tabl[0], tabl, mns->envp));
	}
	else if (pid > 0)
		waitpid(pid, &state, WUNTRACED);
	else
	{
		ft_putstr_fd("Error fork", 1);
		return (-1);
	}
	mns->last_return = WEXITSTATUS(state);
	return (0);
}

int		exec(char **tabl, t_mns *mns)
{
	pid_t	pid;
	int		state;
	int		ret;

	ret = 0;
	state = 0;
	pid = fork();
	if (pid == 0)
	{
		printf("wtf ?\n");
		ret = execve(tabl[0], tabl, mns->envp);
	}
	else if (pid > 0)
		waitpid(pid, &state, WUNTRACED);
	else
	{
		ft_putstr_fd("Error fork", 1);
		return (-1);
	}
	mns->last_return = WEXITSTATUS(state);
	return (ret);
}
