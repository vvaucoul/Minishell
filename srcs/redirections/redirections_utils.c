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

int		r_get_redirection_pos(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (r_is_redirection(tab[i]))
		return (i);
		++i;
	}
	return (FALSE);
}

char **r_get_tab_without_redirection(char **tab)
{
	char **n_tab;
	int i;
	int j;

	i = 0;
	j = 0;
	n_tab = tab;
	while (tab[i])
	{
		if (r_is_redirection(tab[i]))
		++i;
		//else
		n_tab[j] = tab[i];
		++i;
		++j;
	}
	n_tab[j] = NULL;
	return (n_tab);
}

char	**r_get_tab_before_redirection(char **tab)
{
	char **n_tab;
	int i;
	int j;

	i = 0;
	j = 0;
	n_tab = tab;
	while (tab[i] && (!(r_is_redirection(tab[i]))))
	{
		n_tab[j] = tab[i];
		++i;
		++j;
	}
	n_tab[j] = NULL;
	return (n_tab);
}

char	**r_get_tab_after_redirection(char **tab)
{
	char **n_tab;
	int i;
	int j;

	i = 0;
	j = 0;
	n_tab = tab;
	while (tab[i] && (!(r_is_redirection(tab[i]))))
	++i;
	++i;
	printf("assign at [%d]\n", i);
	while (tab[i])
	{
		n_tab[j] = tab[i];
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

char 	**r_get_tab_without_pipe(char **tab)
{
	int i;
	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "|"))
		{
			tab[i] = NULL;
			return (tab);
		}
		++i;
	}
	return (tab);
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

char	**r_update_redirection_tab(char **tab, char **envp, char *redirection)
{
	char			**sysbin_loc;
	int				i;

	if (!(sysbin_loc = get_sysbin_loc(envp)))
	return (NULL);
	i = 0;
	tab[i] = r_update_redirection_tab_make_path(sysbin_loc, tab[i]);
	while (tab[i])
	{
		if ((!(ft_strcmp(tab[i], redirection))) && tab[i + 1])
			tab[i + 1] = r_update_redirection_tab_make_path(sysbin_loc, tab[i + 1]);
		++i;
	}
	tab[i] = NULL;
	return (tab);
}
