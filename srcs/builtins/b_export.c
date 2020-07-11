/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:05:33 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/11 16:08:47 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Does the string contain a '='
*/

static T_BOOL	str_has_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ENV_DELIMITEUR)
		return (1);
		++i;
	}
	return (0);
}

/*
**	Get CMD & Value from line (toto=tata || toto= || toto)
*/

static char		*get_export_cmd(char *line)
{
	return (ft_strtrunc_del(line, ENV_DELIMITEUR));
}

static char		*get_export_value(char *str)
{
	char *value;
	int i;
	int si;
	int j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i++] != ENV_DELIMITEUR);
	if (i == (int)ft_strlen(str))
		return (NULL);
	si = i;
	while (str[i++]);
	if (!(value = malloc(sizeof(char) * ((i - si)))))
	return (NULL);
	while (str[si])
	{
		value[j] = str[si];
		++j;
		++si;
	}
	value[j] = '\0';
	if (j == 0)
		return (NULL);
	return (value);
}

static	T_BOOL	value_already_existing(char **envp, char *str)
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
**	Tab envp functions
*/

static int		get_envp_line(char *cmd, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!(ft_strncmp(cmd, envp[i], ft_strlen(cmd))))
			return (i);
		++i;
	}
	return (-1);
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
	char **nenvp;
	int *size;
	int i;

	i = 0;
	size = get_envp_len(envp[0]);
	if (!(nenvp = malloc(sizeof(char *) * (((size[0] + 1) + (size[1] + 1)) + 1))))
		return (-1);
	while (envp[0][i])
	{
		nenvp[i] = ft_strdup(envp[0][i]);
		++i;
	}
	cmd = ft_strcat(cmd, "=");
	printf("strdup value = %s\n", value);
	if (value)
	nenvp[i] = ft_strdup(ft_strcat(cmd, value));
	else
	nenvp[i] = ft_strdup(cmd);
	nenvp[i + 1] = NULL;
	if (!(envp[0] = malloc(sizeof(char *) * (((size[0] + 1) + (size[1] + 1)) + 1))))
		return (-1);
	set_envp_tab(nenvp, envp);
	free(size);
	return (0);
}

static int		set_envp_value(char *cmd, char *value, T_BOOL already_existing, char ***envp)
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

/*
**	Main export functions
*/

static int		place_env(t_mns *mns, char *line)
{
	T_BOOL 	has_equal;
	T_BOOL	already_existing;
	char	*cmd;
	char	*value;

	has_equal = str_has_equal(line);
	cmd = get_export_cmd(line);
	value = get_export_value(line);
	already_existing = value_already_existing(mns->envp, cmd);

	printf(COLOR_YELLOW); printf("- Has equal = %d\n", has_equal);
	printf(COLOR_YELLOW); printf("- CMD = %s\n", cmd);
	printf(COLOR_YELLOW); printf("- Value = %s\n\n", value);
	printf(COLOR_YELLOW); printf("- Already_existing = %d\n\n", already_existing);

	if (!has_equal && !already_existing)
		return (0);
	set_envp_value(cmd, value, already_existing, &mns->envp);
	return (0);
}

int				b_export(t_mns *mns, char **tab)
{
	int i;

	i = 0;

	printf("tab[0] = %s\n", tab[0]);
	printf("tab[1] = %s\n", tab[1]);

	tab = remove_builtin_in_tab(tab);
	printf(COLOR_YELLOW); printf("Export\n");
	printf(COLOR_GREEN); printf("Found [%s]\n", tab[i]);

	while (tab[i])
	{
		printf(COLOR_GREEN); printf("Found [%s]\n", tab[i]);
		place_env(mns, tab[i]);
		++i;
	}
	return (0);
}
