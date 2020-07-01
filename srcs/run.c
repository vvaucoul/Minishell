/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:34:18 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/06/30 20:07:33 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int		run_builtins(t_mns *mns, char *cmd, char **args, char **envp)
{
	int ret;

	ret = -1;
	printf("\tBuiltin found\n");

	if (!(ft_strcmp(cmd, "pwd")))
	ret = b_pwd(envp, TRUE);

	if (!(ft_strcmp(cmd, "cd")))
	ret = b_cd(mns, args[1]);

	if (!(ft_strcmp(cmd, "echo")))
	ret = b_echo(args, ((!(ft_strcmp(args[1], "-n"))) ? TRUE : FALSE));

	if (!(ft_strcmp(cmd, "export")))
	ret = b_export(mns, args);

	if (!(ft_strcmp(cmd, "unset")))
	ret = b_unset(args, envp);

	if (!(ft_strcmp(cmd, "env")))
	ret = b_env(envp);

	if (!(ft_strcmp(cmd, "exit")))
	ret = b_exit();

	return (ret);
}

int		run(t_mns *mns, char *cmd, char **args, char **envp)
{
	int		*contain_args;
	char	*tmp;

	printf("\tRUN : \n");
	printf("\t- CMD : %s\n", cmd);
	printf("\t- ARGS[0] : %s\n", args[0]);
	printf("\t- ARGS[1] : %s\n\n", args[1]);

	contain_args = parse_arguments(args);

	printf("contain args[0] = %d\n", contain_args[0]);
	printf("contain args[1] = %d\n", contain_args[1]);
	printf("contain args[2] = %d\n", contain_args[2]);


	tmp = args[0];
	args[0] = cmd;
	cmd = tmp;
	if (contain_args[1])
	{
		main_redirections(cmd, args, envp);
		return (0);
	}
	else if (contain_args[2])
	{
		p_pipe(cmd, args, envp);
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
