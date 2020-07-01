/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:32:45 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/06/30 19:35:22 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Redirection 01
**
**	">"
**	EX : ps > s
*/

static int		redirection_01(char **tab_exec, char *output_file, char **envp, T_BOOL use_double)
{
	int	pid;
	int fd;
	int state;

	printf("db 02\n");

	tab_exec = r_get_tab_without_redirection(tab_exec);

	printf("db redirection = ofile = %s | tabexc[0] %s | tabexc[1] %s\n", output_file, tab_exec[0], tab_exec[1]);

	printf(COLOR_RED);
	printf("Redirection 01\n");
	printf(COLOR_NOC);
	if (!output_file)
	{
		ft_putstr_fd("Missing Output\n", 1);
		return (-1);
	}
	if (use_double)
	{
		printf("db 03 - double\n");
		if ((fd = open(output_file, O_WRONLY | O_APPEND | O_CREAT, 0666)) == -1)
		{
			ft_putstr_fd("Error while creating/opening file\n", 1);
			return (-1);
		}
	}
	else
	{
		printf("db 03\n");

		if ((fd = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0666)) == -1)
		{
			ft_putstr_fd("Error while creating/opening file\n", 1);
			return (-1);
		}
	}
	printf("db 04\n");
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 1);

		// checker si c est les builtins ou pas (par exemple pour echo)

		if ((execve(tab_exec[0], tab_exec, envp)) < 0)
		{
			ft_putstr_fd("Error, wront command\n", 1);
			return (-1);
		}
		close(fd);
	}
	else
	waitpid(pid, &state, WUNTRACED);
	printf("db 05\n");
	return (0);
}

/*
**	Redirection 02
**
**	"<"
**	EX : cat < Makefile
*/

static int		redirection_02(char **tab_exec, char *inputfile, char **envp)
{
	int pid;
	int state;
	int fd;
	int fd2;

	printf("db 02\n");
	tab_exec = r_get_tab_without_redirection(tab_exec);

	printf("db redirection = infile = %s | tabexc[0] %s | tabexc[1] %s\n", inputfile, tab_exec[0], tab_exec[1]);

	printf("db 03\n");

	if ((fd = open(inputfile, O_RDONLY)) == -1)
	{
		ft_putstr_fd("Error while creating/opening file\n", 1);
		return (-1);
	}

	printf("db 04\n");
	pid = fork();
	if (pid == 0)
	{
		dup2(fd2, 1);
		if ((execve(tab_exec[0], tab_exec, envp)) < 0)
		{
			ft_putstr_fd("Error, wront command\n", 1);
			return (-1);
		}
		close(fd2);
	}
	else
		waitpid(pid, &state, WUNTRACED);
	printf("db 05\n");
	return (0);
}

/*
**	Switch between all redirections
*/

int		main_redirections(char *cmd, char **tab, char **envp)
{
	int	r_pos;

	printf("db 00\n");
	r_pos = r_get_redirection_pos(tab);
	printf("db 01\n");

	printf("rpos = %d\n", r_pos);

	if (!(ft_strcmp(tab[r_pos], ">")))
	return (redirection_01(tab, tab[r_pos + 1], envp, FALSE));
	if (!(ft_strcmp(tab[r_pos], ">>")))
	return (redirection_01(tab, tab[r_pos + 1], envp, TRUE));
	if (!(ft_strcmp(tab[r_pos], "<")))
	return (redirection_02(tab, tab[r_pos + 1], envp));
	return (0);
}
