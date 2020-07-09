/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 19:23:09 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/09 19:47:05 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void 	do_pipes(char ***tab, char **envp)
{
	int		p[2];
	pid_t	pid;
	int		fd_in = 0;

	while (*tab != NULL)
	{
		pipe(p);
		if ((pid = fork()) == -1)
		exit(EXIT_FAILURE);
		else if (!pid)
		{

			dup2(fd_in, 0);


			if (*(tab + 1) != NULL)
			{

				dup2(p[1], 1);

			}

			close(p[0]);
			execve((*tab)[0], *tab, envp); // fonctionne bien
			//execvp((*tab)[0], *tab); // tmp pour ne pas mettre les /bin/etc a la commande

			exit(EXIT_FAILURE);
		}
		else
		{

			wait(NULL);
			close(p[1]);

			fd_in = p[0];
			tab++;
		}

	}
}

static char	***make_pipe_tab(char **tab_exec)
{
	char	***pipe_tab;
	char	**tmp_tab;
	int		i;
	int		k;
	int		j;

	i = 0;
	j = 0;
	k = 0;
	pipe_tab = malloc(sizeof(char **) * 1000);
	while (tab_exec[i])
	{
		j = 0;
		tmp_tab = malloc(sizeof(char *) * 1000);
		while (tab_exec[i] && (ft_strcmp(tab_exec[i], "|")))
		{
			tmp_tab[j] = ft_strdup(tab_exec[i]);
			++j;
			++i;
		}
		pipe_tab[k] = tmp_tab;
		++k;
		++i;
	}
	return (pipe_tab);
}

int		p_pipe(char **tab_exec, char **envp)
{
	char ***cmd;

	cmd = make_pipe_tab(tab_exec);
	do_pipes(cmd, envp);
	return (0);
}
