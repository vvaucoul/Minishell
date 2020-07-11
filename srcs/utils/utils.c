/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 15:22:26 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/11 11:15:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			exit_shell(void)
{
	write(1, "\n", 1);
	exit(0);
}

int				is_in_quotes(char *str, int pos)
{
	int		quote;
	int		i;

	quote = 0;
	i = 0;
	while (i <= pos)
	{
		if ((str[i] == '\'' && quote == 1) || (str[i] == '"' && quote == 2))
			quote = 0;
		else if (str[i] == '\'' && quote == 0)
			quote = 1;
		else if (str[i] == '"' && quote == 0)
			quote = 2;
		i++;
	}
	i--;
	return ((quote) ? 1 : 0);
}

char			*get_cmd_in_path(char *path)
{
	char *cmd;
	int i;
	int j;
	int k;

	i = ft_strlen(path);
	j = i;
	k = 0;
	while (path[i] != 47 && i > 0)
		--i;
	++i;
	if (!(cmd = malloc(sizeof(char) * (j - i) + 1)))
		return (NULL);
	while (i < j)
	{
		cmd[k] = path[i];
		++i;
		++k;
	}
	cmd[k] = '\0';
	return (cmd);
}

static char	**sort_tab(char **tab, int size, int i)
{
	int si;

	si = 0;
	tab[i] = NULL;
	++i;
	while (si < size)
	{
		tab[si] = tab[si + 1];
		++si;
	}
	tab[si] = NULL;
	return (tab);
}

T_BOOL		b_isvalid(char *str)
{
	if (!(ft_strcmp(str, "echo")))
		return (TRUE);
	if (!(ft_strcmp(str, "cd")))
		return (TRUE);
	if (!(ft_strcmp(str, "env")))
		return (TRUE);
	if (!(ft_strcmp(str, "export")))
		return (TRUE);
	if (!(ft_strcmp(str, "unset")))
		return (TRUE);
	if (!(ft_strcmp(str, "pwd")))
		return (TRUE);
	if (!(ft_strcmp(str, "exit")))
		return (TRUE);
	return (FALSE);
}
