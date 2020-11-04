/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:24:27 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 16:38:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Init Pipes
*/

static t_bool			make_pipe_assign_char(char **tab_exec, char ***pipe_tab,
int *j, int *k)
{
	int i;

	i = 0;
	if (!(pipe_tab[j[0]] = malloc(sizeof(char *) * (MAX_CHAR_IN_PROMPT))))
		return (FALSE);
	while (tab_exec[i])
	{
		if (r_is_pipe(tab_exec[i]))
		{
			pipe_tab[j[0]][k[0]] = NULL;
			++j[0];
			k[0] = 0;
			if (!(pipe_tab[j[0]] = malloc(sizeof(char *)
			* (MAX_CHAR_IN_PROMPT))))
				return (FALSE);
		}
		else
		{
			pipe_tab[j[0]][k[0]] = ft_strdup(tab_exec[i]);
			++k[0];
		}
		++i;
	}
	pipe_tab[j[0] + 1] = NULL;
	return (TRUE);
}

char					***make_pipe_tab(char **tab_exec)
{
	char	***pipe_tab;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (!(pipe_tab = malloc(sizeof(char **) * (ft_full_tablen(tab_exec) *
	MAX_CHAR_IN_PROMPT))))
		return (NULL);
	if (!(make_pipe_assign_char(tab_exec, pipe_tab, &j, &k)))
		return (NULL);
	return (pipe_tab);
}

/*
** Utils
*/

static int				nb_args(char **tab_exec)
{
	int nb;
	int i;

	nb = 0;
	i = 0;
	while (tab_exec[i])
	{
		if (!(r_is_pipe(tab_exec[i])))
			++nb;
		++i;
	}
	return (nb);
}

static int				nb_pipe(char **tab_exec)
{
	int nb;
	int i;

	nb = 0;
	i = 0;
	while (tab_exec[i])
	{
		if (r_is_pipe(tab_exec[i]))
			++nb;
		++i;
	}
	return (nb);
}

/*
** Init structs pipes
*/

int						init_pipe_struct(t_pipe *pipe_s, char **tab_exec)
{
	int i;

	i = 0;
	pipe_s->nb_pipe = nb_pipe(tab_exec);
	pipe_s->nb_args = nb_args(tab_exec);
	if (!(pipe_s->pipe_tab = make_pipe_tab(tab_exec)))
		return (display_error_tf("Malloc Error", NULL, NULL, -1));
	pipe_s->pipe_valid = TRUE;
	pipe_s->fd_prev = 0;
	pipe_s->current_pipe = 0;
	if (!(pipe_s->ac_pipes = malloc(sizeof(t_cpipe) * (pipe_s->nb_args + 1))))
		return (display_error_tf("Malloc Error", NULL, NULL, -1));
	while (i < pipe_s->nb_args)
	{
		pipe_s->ac_pipes[i].pid = 0;
		pipe_s->ac_pipes[i].status = 0;
		++i;
	}
	return (0);
}
