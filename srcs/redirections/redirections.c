/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:32:45 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/14 17:25:52 by vvaucoul         ###   ########.fr       */
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

	if (!output_file)
	{
		ft_putstr_fd("Missing Output\n", 1);
		return (0);
	}
	if (use_double)
	{
		if ((fd = open(output_file, O_WRONLY | O_APPEND | O_CREAT, 0666)) == -1)
		{
			display_error("Error while creating/opening file\n");
			return (0);
		}
	}
	else
	{
		if ((fd = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0666)) == -1)
		{
			display_error("Error while creating/opening file\n");
			return (0);
		}
	}
	tab_exec = r_update_redirection_tab(tab_exec, envp, (use_double ? ">>" : ">"));
	tab_exec = r_get_tab_before_redirection(tab_exec);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 1);

		// checker si c est les builtins ou pas (par exemple pour echo)

		if ((execve(tab_exec[0], tab_exec, envp)) < 0)
		{
			ft_putstr_fd("Error, wrong command\n", 1);
			return (0);
		}
		close(fd);
	}
	else
	waitpid(pid, &state, WUNTRACED);
	return (0);
}

/*
**	Redirection 02
**
**	"<"
**	EX : cat < Makefile
*/

static int		redirection_02(char **tab_exec, char **envp)
{
	int pid;
	int state;
	int fd;

	tab_exec = r_update_redirection_tab(tab_exec, envp, "<");
	tab_exec = r_get_tab_without_redirection(tab_exec);
	fd = open(tab_exec[1], O_RDONLY);
	tab_exec[1] = NULL;
	// print_table(tab_exec, "tabl exec redirection");
	if (!(pid = fork()))
	{
		dup2(fd, 0);
		close(fd);
		execve(tab_exec[0], tab_exec, NULL);
	}
	else
	{
		close(fd);
		waitpid(pid, &state, WUNTRACED);
	}
	return (0);
}


/*
**	Switch between all redirections
*/

int		main_redirections(char **tabl, char **envp)
{
	int	r_pos;

	r_pos = r_get_redirection_pos(tabl);
	if (!(ft_strcmp(tabl[r_pos], ">")))
	return (redirection_01(tabl, tabl[r_pos + 1], envp, FALSE));
	if (!(ft_strcmp(tabl[r_pos], ">>")))
	return (redirection_01(tabl, tabl[r_pos + 1], envp, TRUE));
	if (!(ft_strcmp(tabl[r_pos], "<")))
	return (redirection_02(tabl, envp));
	if (BONUS)
	{
		if (!(ft_strcmp(tabl[r_pos], "<<")))
		return (bonus_redirection(tabl, envp));
	}
	return (0);
}
