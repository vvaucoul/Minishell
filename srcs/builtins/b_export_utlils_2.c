/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_utlils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 18:11:28 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/27 18:40:13 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

T_BOOL			value_already_existing(char **envp, char *str)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!(ft_strncmp(envp[i], str, ft_strlen(str))))
			return (TRUE);
		++i;
	}
	return (FALSE);
}

/*
**	Place line into envp
*/

static int		*get_envp_len(char **envp)
{
	int *size;
	int i;
	int j;
	int mj;

	i = 0;
	j = 0;
	mj = 0;
	size = malloc(sizeof(int) * 2);
	while (envp[i])
	{
		while (envp[i][j])
			++j;
		if (j > mj)
			mj = j;
		++i;
		j = 0;
	}
	size[0] = i;
	size[1] = mj;
	return (size);
}

static int		set_envp_tab(char **nenvp, char ***envp)
{
	int i;

	i = 0;
	while (nenvp[i])
	{
		envp[0][i] = ft_strdup(nenvp[i]);
		++i;
	}
	envp[0][i] = NULL;
	return (0);
}

static int		realloc_envp(char *cmd, char *value, char ***envp)
{
	char	**nenvp;
	int		*size;
	int		i;

	size = get_envp_len(envp[0]);
	if (!(nenvp = malloc(sizeof(char *) * (((size[0] + 1) + (size[1] + 1))
	+ 1))))
		return (-1);
	i = -1;
	while (envp[0][++i])
		nenvp[i] = ft_strdup(envp[0][i]);
	cmd = ft_strcat(cmd, "=");
	if (value)
		nenvp[i] = ft_strdup(ft_strcat(cmd, value));
	else
		nenvp[i] = ft_strdup(cmd);
	nenvp[i + 1] = NULL;
	if (!(envp[0] = malloc(sizeof(char *) * (((size[0] + 1) + (size[1] + 1))
	+ 1))))
		return (-1);
	set_envp_tab(nenvp, envp);
	free(size);
	return (0);
}

int				set_envp_value(char *cmd, char *value, T_BOOL already_existing,
char ***envp)
{
	int line;

	line = get_envp_line(cmd, envp[0]);
	if (line < 0)
		realloc_envp(cmd, value, envp);
	else
	{
		if (already_existing && !value)
			return (0);
		cmd = ft_strcat(cmd, "=");
		envp[0][line] = ft_strdup(ft_strcat(cmd, value));
	}
	return (0);
}
