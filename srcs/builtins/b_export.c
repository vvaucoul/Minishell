/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 14:05:33 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/06/30 13:54:55 by root             ###   ########.fr       */
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
	while (str[i] && str[i++] != ENV_DELIMITEUR);
	si = i;
	//printf(COLOR_CYAN); //printf("\nexport value | si = %d |\n", si);
	while (str[i++]);
	if (!(value = malloc(sizeof(char) * ((i - si)))))
	return (NULL);
	//printf(COLOR_CYAN); //printf("export value | malloc = %d |\n", ((i - si)));

	//printf(COLOR_CYAN); //printf("export value | si = %d | j = %d |\n", si, j);
	while (str[si])
	{
		value[j] = str[si];
		++j;
		++si;
	}
	//printf(COLOR_CYAN); //printf("export value | value = %s |\n\n", value);

	value[j] = '\0';
	return (value);
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

static int		set_envp_tab(int *size, char **nenvp, char ***envp)
{
	int i;

	//printf(COLOR_YELLOW); //printf("Change envp\n");
	i = 0;
	while (nenvp[i])
	{
		envp[0][i] = ft_strdup(nenvp[i]);
		//printf(COLOR_CYAN);	//printf("envp[0][%d] = %s\n", i, envp[0][i]);
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

	//printf(COLOR_VIOLET); //printf("\nrealloc envp : size[0] = %d | size[1] = %d\n", size[0], size[1]);

	if (!(nenvp = malloc(sizeof(char *) * (((size[0] + 1) + (size[1] + 1)) + 1))))
	return (-1);
	while (envp[0][i])
	{
		nenvp[i] = ft_strdup(envp[0][i]);
		++i;
	}
	//printf(COLOR_VIOLET); //printf("realloc envp : added %d lines\n", i);
	cmd = ft_strcat(cmd, "=");
	nenvp[i] = ft_strdup(ft_strcat(cmd, value));
	//printf(COLOR_VIOLET); //printf("realloc envp : last line = %s\n", nenvp[i]);
	nenvp[i + 1] = NULL;

	if (!(envp[0] = malloc(sizeof(char *) * (((size[0] + 1) + (size[1] + 1)) + 1))))
		return (-1);
	//printf("malloc envp\n");
	set_envp_tab(size, nenvp, envp);
	//printf("end set env\n");
	free(size);
	//printf(COLOR_YELLOW); //printf("\nadded new line\n");
	return (0);
}

static int		set_envp_value(char *cmd, char *value, char ***envp)
{
	int line;

	line = get_envp_line(cmd, envp[0]);
	//printf(COLOR_YELLOW); //printf("- LINE = %d\n", line);

	if (line < 0)
		realloc_envp(cmd, value, envp);
	else
	{
		cmd = ft_strcat(cmd, "=");
		envp[0][line] = ft_strdup(ft_strcat(cmd, value));
	}
	return (0);
}

/*
**	Main export functions
*/

static int		place_env(char *line, char ***envp)
{
	T_BOOL 	has_equal;
	char	*cmd;
	char	*value;

	has_equal = str_has_equal(line);
	cmd = get_export_cmd(line);
	value = get_export_value(line);

	//printf(COLOR_YELLOW); //printf("- Has equal = %d\n", has_equal);
	//printf(COLOR_YELLOW); //printf("- CMD = %s\n", cmd);
	//printf(COLOR_YELLOW); //printf("- Value = %s\n\n", value);

	set_envp_value(cmd, value, envp);
	//printf("check envp 02 | envp[63] = %s\n", envp[0][63]);
	return (0);
}

int				b_export(t_mns *mns, char **tab)
{
	int i;

	i = 0;
	//printf(COLOR_YELLOW); //printf("Export\n");
	while (tab[i])
	{
		place_env(tab[i], &mns->envp);
		++i;
	}
	return (0);
}
