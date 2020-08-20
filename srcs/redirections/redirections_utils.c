/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:40:16 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/14 17:16:26 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	REDIRECTIONS
*/


T_BOOL	r_is_redirection(char *str)
{
	if (!(ft_strcmp(str, ">")))
	return (TRUE);
	else if (!(ft_strcmp(str, ">>")))
	return (TRUE);
	else if (!(ft_strcmp(str, "<")))
	return (TRUE);
	else if ((!(ft_strcmp(str, "<<"))) && BONUS)
	return (TRUE);
	return (FALSE);
}

int		r_get_redirection_pos(char **tabl)
{
	int i;

	i = 0;
	while (tabl[i])
	{
		if (r_is_redirection(tabl[i]))
		return (i);
		++i;
	}
	return (FALSE);
}

char **r_get_tab_without_redirection(char **tabl)
{
	char **n_tab;
	int i;
	int j;

	i = 0;
	j = 0;
	n_tab = tabl;
	while (tabl[i])
	{
		if (r_is_redirection(tabl[i]))
		++i;
		//else
		n_tab[j] = tabl[i];
		++i;
		++j;
	}
	n_tab[j] = NULL;
	return (n_tab);
}

char	**r_get_tab_before_redirection(char **tabl)
{
	char **n_tab;
	int i;
	int j;

	i = 0;
	j = 0;
	n_tab = tabl;
	while (tabl[i] && (!(r_is_redirection(tabl[i]))))
	{
		n_tab[j] = tabl[i];
		++i;
		++j;
	}
	n_tab[j] = NULL;
	return (n_tab);
}

char	**r_get_tab_after_redirection(char **tabl)
{
	char **n_tab;
	int i;
	int j;

	i = 0;
	j = 0;
	n_tab = tabl;
	while (tabl[i] && (!(r_is_redirection(tabl[i]))))
	++i;
	++i;
	printf("assign at [%d]\n", i);
	while (tabl[i])
	{
		n_tab[j] = tabl[i];
		++i;
		++j;
	}
	n_tab[j] = NULL;
	printf("return [%s]\n", n_tab[0]);
	return (n_tab);
}

/*
**	PIPES
*/

char 	**r_get_tab_without_pipe(char **tabl)
{
	int i;
	i = 0;
	while (tabl[i])
	{
		if (ft_strcmp(tabl[i], "|"))
		{
			tabl[i] = NULL;
			return (tabl);
		}
		++i;
	}
	return (tabl);
}

/*
**	Redirecitons Make Path
*/

static	char *r_update_redirection_tab_make_path(char **sysbin_loc, char *str)
{
	char			*path;
	int				i;
	struct stat		stat;

	i = 0;
	while (sysbin_loc && sysbin_loc[i])
	{
		if (ft_strstartswith(str, sysbin_loc[i], 0, 0))
			path = ft_strdup(str);
		else
			path = ft_strjoin(sysbin_loc[i], str);
		if (lstat(path, &stat) == -1)
			free(path);
		else
			return (path);
		++i;
	}
	return (str);
}

char	**r_update_redirection_tab(char **tabl, char **envp, char *redirection)
{
	char			**sysbin_loc;
	int				i;

	if (!(sysbin_loc = get_sysbin_loc(envp)))
	return (NULL);
	i = 0;
	tabl[i] = r_update_redirection_tab_make_path(sysbin_loc, tabl[i]);
	while (tabl[i])
	{
		if ((!(ft_strcmp(tabl[i], redirection))) && tabl[i + 1])
			tabl[i + 1] = r_update_redirection_tab_make_path(sysbin_loc, tabl[i + 1]);
		++i;
	}
	tabl[i] = NULL;
	return (tabl);
}
