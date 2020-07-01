/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 19:23:09 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/06/30 19:59:15 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	**p_adjust_pipe_tab(char **tab)
{
	char **fp_tab;
	int i;

	i = 0;
	if (!(fp_tab = malloc(sizeof(char *) * 3)))
	return (NULL);
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "|"))
		{
			fp_tab[0] = tab[i - 1];
			fp_tab[1] = tab[i + 1];
			fp_tab[2] = NULL;
			return (fp_tab);
		}
		++i;
	}
	return (NULL);
}

int		p_pipe(char *cmd, char **tab_exec, char **envp)
{
	int	fd[2];
	int pid;
	int state;
	char **fp_tab;

	printf("debug 01\n");

	if (!(fp_tab = p_adjust_pipe_tab(tab_exec)))
	return (-1);

	//tab_exec = r_get_tab_without_pipe(tab_exec);

	printf("debug 02\n");

	pipe(fd);

	printf("fd[0] = %d\n", fd[0]);
	printf("fd[1] = %d\n", fd[1]);

	printf("debug 03\n");

	pid = fork();
	if (!pid)
	{
		printf("debug 04\n");


		printf("cmd[0] = %s\n", tab_exec[0]);
		printf("cmd[1] = %s\n", tab_exec[1]);
		printf("cmd[2] = %s\n", tab_exec[2]);
		printf("cmd[3] = %s\n", tab_exec[3]);
		printf("cmd[4] = %s\n", tab_exec[4]);

		dup2(fd[1], 1);
		if ((execve(tab_exec[0], tab_exec, envp)) < 0)
		{
			ft_putstr_fd("Error, wront command\n", 1);
			return (-1);
		}
	}
	else
	{
		printf("debug 05\n");
		dup2(fd[0], 0);
		close(fd[1]);
	//	waitpid(pid, &state, WUNTRACED);
	}
	printf("debug 06\n");

	if ((execve(tab_exec[0], tab_exec, envp)) < 0)
	{
		ft_putstr_fd("Error, wront command\n", 1);
		return (-1);
	}

	free(fp_tab);
	return (0);
}

/*
for( i=1; i<argc-1; i++)
{
	int pd[2];
	pipe(pd);

	if (!fork()) {
		dup2(pd[1], 1); // remap output back to parent
		execlp(argv[i], argv[i], NULL);
		perror("exec");
		abort();
	}

	// remap output from previous child to input
	dup2(pd[0], 0);
	close(pd[1]);
}

execlp(argv[i], argv[i], NULL);
perror("exec");
abort();
*/
