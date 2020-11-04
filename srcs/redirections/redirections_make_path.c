/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_make_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:01:35 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 16:45:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Utils make path
*/

void			append_path_tab_make_path_init(int *i, char **path)
{
	*i = 0;
	*path = NULL;
}

char			*append_path_tab_make_path(char **sysbin_loc, char *str,
struct stat stat)
{
	char			*path;
	int				i;

	append_path_tab_make_path_init(&i, &path);
	while (sysbin_loc && sysbin_loc[i])
	{
		if (ft_strstartswith(str, sysbin_loc[i], 0, 0))
			path = ft_strdup(str);
		else
		{
			if (!i)
				path = ft_strdup(str);
			else
				path = ft_strjoin(sysbin_loc[i], str);
		}
		if (lstat(path, &stat) == -1)
			free(path);
		else
		{
			free(str);
			return (path);
		}
		++i;
	}
	return (str);
}

char			**append_path_tab(char **cmd_tab, char **envp)
{
	struct stat		stat;
	char			**sysbin_loc;
	int				i;

	if (!(sysbin_loc = get_sysbin_loc(envp)))
		return (NULL);
	i = 0;
	while (cmd_tab[i] && (!(r_is_redirection(cmd_tab[i]))))
	{
		if (i - 1 > 0)
			if (!(b_isvalid(cmd_tab[i]) && (r_is_redirection(cmd_tab[i - 1]))))
				cmd_tab[i] = append_path_tab_make_path(sysbin_loc, cmd_tab[i],
			stat);
		++i;
	}
	ft_freetab(sysbin_loc);
	return (cmd_tab);
}
