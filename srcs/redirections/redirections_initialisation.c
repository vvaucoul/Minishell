/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_initialisation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:00:47 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/10/20 18:18:16 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			sort_args_start(char **tabl, char ***cmd_tab, int *i,
int *k)
{
	i[0] = 0;
	k[0] = 0;
	while (tabl[i[0]])
	{
		if (r_is_redirection(tabl[i[0]]))
			break ;
		else
			cmd_tab[0][k[0]] = ft_strdup(tabl[i[0]]);
		++i[0];
		++k[0];
	}
}

char				**sort_args(char **tabl)
{
	char	**cmd_tab;
	int		i;
	int		j;
	int		k;

	if (!(cmd_tab = malloc(sizeof(char *) * ft_full_tablen(tabl))))
		return (NULL);
	sort_args_start(tabl, &cmd_tab, &i, &k);
	while (tabl[i])
	{
		if (r_is_redirection(tabl[i]))
		{
			j = i + 2;
			while (tabl[j] && (!(r_is_redirection(tabl[j]))))
			{
				cmd_tab[k] = ft_strdup(tabl[j]);
				++k;
				++j;
			}
		}
		++i;
	}
	cmd_tab[k] = NULL;
	return (cmd_tab);
}

char				**sort_redir(char **tabl, int start)
{
	char	**redir_tab;
	int		i;
	int		k;

	i = start;
	k = 0;
	if (!(redir_tab = malloc(sizeof(char *) * ft_full_tablen(tabl))))
		return (NULL);
	while (tabl[i])
	{
		if (r_is_redirection(tabl[i]))
		{
			redir_tab[k] = ft_strdup(tabl[i]);
			redir_tab[k + 1] = ft_strdup(tabl[i + 1]);
			k += 2;
		}
		++i;
	}
	redir_tab[k] = NULL;
	return (redir_tab);
}

char				**final_redir_tab(char **cmd_tab, char **redir_tab)
{
	char	**final_redir_tab;
	int		i;
	int		k;

	if (!(final_redir_tab = malloc(sizeof(char *) * (ft_full_tablen(cmd_tab) *
	ft_full_tablen(redir_tab)))))
		return (NULL);
	i = 0;
	k = 0;
	while (cmd_tab[i])
	{
		final_redir_tab[k] = ft_strdup(cmd_tab[i]);
		++k;
		++i;
	}
	i = 0;
	while (redir_tab[i])
	{
		final_redir_tab[k] = ft_strdup(redir_tab[i]);
		++i;
		++k;
	}
	final_redir_tab[k] = NULL;
	return (final_redir_tab);
}

int					multiple_redirection_suite(char **tabl)
{
	int redir;
	int i;

	i = 0;
	redir = 0;
	while (tabl[i])
	{
		if (r_is_redirection(tabl[i]))
		{
			if (r_get_redirection_type(tabl[i]) == redir)
				return (redir);
			redir = r_get_redirection_type(tabl[i]);
		}
		else
			redir = 0;
		++i;
	}
	return (0);
}
