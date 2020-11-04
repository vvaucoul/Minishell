/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:04:22 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 16:41:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Free redirections
*/

int					free_redirections(t_redirection *redir)
{
	ft_freetab(redir->cmd_tab);
	ft_freetab(redir->redir_tab);
	ft_freetab(redir->final_redir_tab);
	return (TRUE);
}

/*
** Redirections erreurs
*/

t_bool				redirections_error(char **tabl)
{
	int redir;

	if ((redir = (multiple_redirection_suite(tabl))))
	{
		if (redir == 1)
			display_error("syntax error near unexpected token `>'");
		if (redir == 2)
			display_error("syntax error near unexpected token `>>'");
		if (redir == 3)
			display_error("syntax error near unexpected token `<'");
		if (redir == 4)
			display_error("syntax error near unexpected token `<<'");
		return (1);
	}
	if (last_arg_is_redirection(tabl))
	{
		display_error("syntax error near unexpected token `newline'");
		return (1);
	}
	return (0);
}

/*
** Init Redirection struct
*/

t_redirection		init_redirection_struct(char **tabl, char **envp)
{
	t_redirection	redir;

	redir.first_redir_pos = find_first_redirection_pos(tabl);
	redir.nb_redir = count_redir(tabl);
	redir.cmd_tab = sort_args(tabl);
	redir.cmd_tab = append_path_tab(redir.cmd_tab, envp);
	redir.redir_tab = sort_redir(tabl, redir.first_redir_pos);
	redir.final_redir_tab = final_redir_tab(redir.cmd_tab, redir.redir_tab);
	redir.final_redir_tab = append_path_tab(redir.final_redir_tab,
	redir.redir_tab);
	redir.actu_redir = 0;
	redir.redir_valid = FALSE;
	return (redir);
}
