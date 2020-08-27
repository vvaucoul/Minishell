/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 19:23:09 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/27 16:58:25 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_pipes(char ***tabl, char **envp)
{
	int		p[2];
	pid_t	pid;
	int		fd_in = 0;
	int 	state;

	while (*tabl != NULL)
	{
		pipe(p);
		if ((pid = fork()) == -1)
			exit(EXIT_FAILURE);
		else if (!pid)
		{
			// print_table((*tabl), "Pipe tabl : ");
			dup2(fd_in, 0);
			if (*(tabl + 1) != NULL)
				dup2(p[1], 1);
			close(p[0]);
			execve((*tabl)[0], *tabl, envp); // fonctionne bien
			//execvp((*tabl)[0], *tabl); // tmp pour ne pas mettre les /bin/etc a la commande
			exit(EXIT_FAILURE);
		}
		else
		{
			//wait(NULL);
			waitpid(pid, &state, WUNTRACED);
			close(p[1]);
			fd_in = p[0];
			tabl++;
		}
	}
	return (WEXITSTATUS(state));
}

static char	***make_pipe_tab(char **tab_exec, int maxsize)
{
	char	***pipe_tab;
	char	**under_pipe_tab;
	int		i;
	int		k;
	int		j;

	i = 0;
	j = 0;
	k = 0;
	// calculer la taille des mallocs [to do !!!]
	pipe_tab = malloc(sizeof(char **) * 10000);
	while (tab_exec[i])
	{
		//printf("tab_exec[%d] = %s\n", i, tab_exec[i]);
		j = 0;
		// calculer la taille des mallocs [to do !!!]
		under_pipe_tab = malloc(sizeof(char *) * 10000);
		while (tab_exec[i] && (ft_strcmp(tab_exec[i], "|")))
		{
			under_pipe_tab[j] = ft_strdup(tab_exec[i]);
			//printf("\t - under_pipe_tab[%d] = %s\n", j, under_pipe_tab[j]);
			++j;
			++i;
		}
		under_pipe_tab[j] = NULL;
		pipe_tab[k] = under_pipe_tab;
		++k;
		++i;
		//printf("end i [%d]\n", i);
		if (i > maxsize)
		{
			pipe_tab[k] = NULL;
			return (pipe_tab);
		}
	}
	pipe_tab[k] = NULL;
	return (pipe_tab);
}

int		p_pipe(char **tab_exec, char **envp)
{
	char ***pipe_tab;

	// print_table(tab_exec, "Pipe Table : ");

	tab_exec = r_update_redirection_tab(tab_exec, envp, "|");

	// print_table(tab_exec, "Pipe Table after update : ");

	pipe_tab = make_pipe_tab(tab_exec, tab_len(tab_exec));

	return(do_pipes(pipe_tab, envp)); // return la valeur de retour du dernier pipe
}
