/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:30:05 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 19:49:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		unser_make_envp_new(char ***envp, char **new_envp)
{
	int		y;
	int		i;

	y = 0;
	i = 0;
	while (envp[0][y])
	{
		free(envp[0][y]);
		++y;
	}
	while (new_envp[i])
	{
		envp[0][i] = ft_strdup(new_envp[i]);
		++i;
	}
	envp[0][i] = NULL;
	return (0);
}

static	int		unset_make_envp(char ***envp, const int si)
{
	char	**new_envp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(new_envp = malloc(sizeof(char *) * (ft_full_tablen(envp[0])))))
		return (-1);
	while (envp[0][i])
	{
		if (i != si)
		{
			new_envp[j] = ft_strdup(envp[0][i]);
			++j;
		}
		++i;
	}
	new_envp[j] = NULL;
	unser_make_envp_new(envp, new_envp);
	ft_freetab(new_envp);
	return (0);
}

static int		unset_remove(char *line, char **envp)
{
	int envp_line;

	if ((envp_line = get_envp_line(line, envp, ENV_DELIMITEUR)) != -1)
	{
		if ((unset_make_envp(&envp, envp_line)) == -1)
			return (-1);
	}
	return (0);
}

static	int		unset_errors(t_mns *mns, char **tabl, int start)
{
	int i;

	i = start;
	if (ft_tablen(tabl) == 1)
		return (display_error_tf("unset: ", NULL, "not enough arguments", 1));
	while (tabl[i])
	{
		if (ft_strrange(tabl[i], STRNG))
		{
			return (update_last_return(mns, display_error_tf("unset: ", tabl[i],
			": invalid parameter name", 1)));
		}
		++i;
	}
	return (0);
}

int				b_unset(t_mns *mns, char **tabl, char **envp)
{
	int i;

	i = 1;
	while (tabl[i])
	{
		if (!(unset_errors(mns, tabl, i)))
			unset_remove(tabl[i], envp);
		++i;
	}
	return (1);
}
