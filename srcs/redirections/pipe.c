/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 19:23:09 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/08 16:15:51 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	char **p_adjust_pipe_tab_before(char **tab, int pipe)
// {
// 	char **pipe_tab_before;
// 	int i;
// 	int ac_pipe;
// 	int k;
//
// 	i = 0;
// 	ac_pipe = 0;
// 	k = 0;
//
// 	while (ac_pipe < pipe)
// 	{
// 		if (!(ft_strcmp(tab[i], "|")))
// 		++ac_pipe;
// 		++i;
// 	}
//
// 	printf("actu tab[%d] = %s\n", i, tab[i]);
//
// 	pipe_tab_before = malloc(sizeof(char *) * 100);
// 	while (ft_strcmp(tab[i], "|") && tab[i])
// 	{
// 		pipe_tab_before[i] = tab[i];
// 		++i;
// 	}
// 	pipe_tab_before[i] = NULL;
// 	return (pipe_tab_before);
// }
//
// static	char **p_adjust_pipe_tab_after(char **tab, int pipe)
// {
// 	char **pipe_tab_after;
// 	int i;
// 	int ac_pipe;
// 	int k;
//
// 	i = 0;
// 	ac_pipe = 0;
// 	k = 0;
//
// 	while (ac_pipe < pipe)
// 	{
// 		if (!(ft_strcmp(tab[i], "|")))
// 		++ac_pipe;
// 		++i;
// 	}
// 	pipe_tab_after = malloc(sizeof(char *) * 100);
// 	while (ft_strcmp(tab[i], "|") && tab[i])
// 	++i;
// 	++i;
// 	printf("after tab[%d] = %s\n", i, tab[i]);
// 	while (tab[i] && ft_strcmp(tab[i], "|"))
// 	{
// 		pipe_tab_after[k++] = tab[i];
// 		++i;
// 	}
// 	pipe_tab_after[k] = NULL;
// 	return (pipe_tab_after);
// }
//
// static	int	get_pipe_number(char **tab)
// {
// 	int i;
// 	int	np;
//
// 	i = 0;
// 	np = 0;
// 	while (tab[i++])
// 	{
// 		if (!(ft_strcmp(tab[i], "|")))
// 		++np;
// 	}
// 	return (np);
// }

static void printtable(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		ft_putstr_fd("\n", 1);
		++i;
	}
}

static void 	do_pipes(char ***tab, char **envp)
{
	int		p[2];
	pid_t	pid;
	int		fd_in = 0;
	int state;

	while (*tab != NULL)
	{
		pipe(p);
		if ((pid = fork()) == -1)
		exit(EXIT_FAILURE);
		else if (!pid)
		{
			printf("TEST 1\n");
			dup2(fd_in, 0);
			printf("TEST 2\n");
			printf("tab = %s\n", **tab);
			if (*(tab + 1) != NULL)
			{
				printf("JE SUIS LAAAAAAAAAAAA\n");
				dup2(p[1], 1);
				printf("JE SUIS GIGA LAAAAAAAAAAAA\n");
			}
			printf("TEST 2 passe wesh\n");
			close(p[0]);
			// execve((*tab)[0], *tab, envp); // fonctionne bien
			 execvp((*tab)[0], *tab); // tmp pour ne pas mettre les /bin/etc a la commande
			printf("TEST 3\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("TEST 4\n");
			wait(NULL);
			close(p[1]);
			printf("TEST 5\n");
			fd_in = p[0];
			tab++;
		}
		printf("TEST 6\n");
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

	printf("01\n");
	pipe_tab = malloc(sizeof(char **) * 1000);

	while (tab_exec[i])
	{
		printf("i = %d\n", i);
		j = 0;
		tmp_tab = malloc(sizeof(char *) * 1000);
		while (tab_exec[i] && (ft_strcmp(tab_exec[i], "|")))
		{
			printf("j = %d\n", j);
			tmp_tab[j] = ft_strdup(tab_exec[i]);
			++j;
			++i;
		}
		printf("k = %d\n", k);
		pipe_tab[k] = tmp_tab;
		++k;
		++i;
	}


	printf("01\n");

	return (pipe_tab);
}

int		p_pipe(char **tab_exec, char **envp)
{
	/*
	char *ls[] = {"/bin/ls", "-al", NULL};
	char *rev[] = {"/usr/bin/rev", NULL};
	char *nl[] = {"/usr/bin/nl", NULL};
	char *cat[] = {"/bin/cat", "-e", NULL};

	char **cmd[] = {ls, rev, nl, cat, NULL};
	*/

	char ***cmd = make_pipe_tab(tab_exec);

	printf("table cmd [0]\n");
	printtable(cmd[0]);
	printf("table cmd [1]\n");
	printtable(cmd[1]);

	do_pipes(cmd, envp);
	return (0);

	/*
	int i;
	int actu_pipe;
	int npipes;

	char **pipe_tab_before;
	char **pipe_tab_after;

	i = 0;
	actu_pipe = 0;
	npipes = get_pipe_number(tab_exec);


	while (i < npipes)
	{
	int pd[2];

	pipe(pd);
	if (!fork()) {
	dup2(pd[1], 1); // remap output back to parent

	pipe_tab_before = p_adjust_pipe_tab_before(tab_exec, actu_pipe);

	printtable(pipe_tab_before);

	execve(pipe_tab_before[0], pipe_tab_before, envp);
	perror("exec");
	abort();
}
++actu_pipe;
// remap output from previous child to input
dup2(pd[0], 0);
close(pd[1]);
++i;
}

//printtable(pipe_tab_after);

pipe_tab_after = p_adjust_pipe_tab_after(tab_exec, actu_pipe);

execve(pipe_tab_after[0], pipe_tab_after, envp);
perror("exec");
abort();
*/

/*
int state;
int actu_pipe;
int i;
int k;
int *pipes;
int npipes;

char **pipe_tab_before;
char **pipe_tab_after;


npipes = get_pipe_number(tab_exec);

pipes = malloc(sizeof(int) * npipes + 1);

k = 0;
while (i < npipes)
{
pipe(pipes + k);
k += 2;
++i;
}

k = 0;
actu_pipe = 0;

if (!(fork()))
{
dup2(pipes[k + 1], 1);

i = 0;
while (i < npipes)
{
close(pipes[i]);
++i;
}

pipe_tab_before = p_adjust_pipe_tab_before(tab_exec, actu_pipe);

if ((execve(pipe_tab_before[0], pipe_tab_before, envp)) < 0)
{
ft_putstr_fd("[0] Error, wrong command\n", 1);
return (-1);
}
}
else
{
if (fork() == 0)
{
dup2(pipes[k], 0);
dup2(pipes[k + 3], 0);

i = 0;
while (i < npipes)
{
close(pipes[i]);
++i;
}

pipe_tab_after = p_adjust_pipe_tab_after(tab_exec, actu_pipe);

if ((execve(pipe_tab_after[0], pipe_tab_after, envp)) < 0)
{
ft_putstr_fd("[0] Error, wrong command\n", 1);
return (-1);
}
}
else
{
if (fork() == 0)
{
dup2(pipes[k + 2], 0);

i = 0;
while (i < npipes)
{
close(pipes[i]);
++i;
}

pipe_tab_before = p_adjust_pipe_tab_before(tab_exec, actu_pipe + 1);

if ((execve(pipe_tab_before[0], pipe_tab_before, envp)) < 0)
{
ft_putstr_fd("[0] Error, wrong command\n", 1);
return (-1);
}

}
}
}

*/
return (0);
}


/*
**	Work with Single pipe
*/


/*
int		p_pipe(char *cmd, char **tab_exec, char **envp)
{
int	pipefd[2];
int pipe_pid;
int pid;
int state;

// a decommenter quand y aura le code de matthieu

char *pipe_tab_before[] = {"/bin/ps", "aux", NULL};
char *pipe_tab_after[] = {"/usr/bin/grep", "minishell", NULL};

//char **pipe_tab_before;
//char **pipe_tab_after;

//pipe_tab_before = p_adjust_pipe_tab_before(tab_exec);
//pipe_tab_after = p_adjust_pipe_tab_after(tab_exec);

printf(COLOR_CYAN);
printf("tab After [0] = %s\n", pipe_tab_after[0]);
printf("tab After [1] = %s\n\n", pipe_tab_after[1]);

printf(COLOR_RED);
printf("tab Before [0] = %s\n", pipe_tab_before[0]);
printf("tab Before [1] = %s\n\n", pipe_tab_before[1]);

printf(COLOR_NOC);

pid = fork();

if (pid == 0)
{
pipe(pipefd);
pipe_pid = fork();
if (pipe_pid == 0)
{
dup2(pipefd[0], 0);
close(pipefd[1]);
if ((execve(pipe_tab_after[0], pipe_tab_after, envp)) < 0)
{
ft_putstr_fd("[0] Error, wrong command\n", 1);
return (-1);
}
}
else
{
dup2(pipefd[1], 1);
close(pipefd[0]);
if ((execve(pipe_tab_before[0], pipe_tab_before, envp)) < 0)
{
ft_putstr_fd("[1] Error, wrong. command\n", 1);
return (-1);
}
}
}
else
waitpid(pid, &state, WUNTRACED);
return (0);
}
*/
