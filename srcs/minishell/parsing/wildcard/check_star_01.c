/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_star_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 22:40:19 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/03 17:40:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_linksnum(char *path)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				i;
	char			*finalpath;

	if (path[0] == '/')
		finalpath = ft_strdup(path);
	else
		finalpath = ft_strjoin("./", path);
	if ((dirp = opendir(finalpath)) == NULL)
	{
		free(finalpath);
		return (0);
	}
	free(finalpath);
	i = 0;
	while ((dp = readdir(dirp)) != NULL)
		i++;
	closedir(dirp);
	return (i);
}

int		remove_from_tab(char ***list, int i)
{
	int size;

	size = ft_tablen(list[0]);
	if (i >= size)
		return (0);
	free(list[0][i]);
	while (list[0][++i - 1])
		list[0][i - 1] = list[0][i];
	return (0);
}

void	remove_hidden(char ***list)
{
	int		i;

	i = 0;
	while (list[0][i])
	{
		while (list[0][i] && list[0][i][0] == '.')
			remove_from_tab(list, i);
		i++;
	}
}

char	**get_linkslist(char *path)
{
	char			**list;
	DIR				*dirp;
	struct dirent	*dp;
	int				i;
	char			*finalpath;

	if ((i = get_linksnum(path)) == -1)
		return (NULL);
	if (!(list = ft_calloc(i + 1, sizeof(char*))))
		return (NULL);
	if (path[0] == '/')
		finalpath = ft_strdup(path);
	else
		finalpath = ft_straddstr("./", path, 0);
	dirp = opendir(finalpath);
	free(finalpath);
	if (dirp == NULL)
		return (list);
	i = 0;
	while ((dp = readdir(dirp)) != NULL)
		list[i++] = ft_strdup(dp->d_name);
	closedir(dirp);
	remove_hidden(&list);
	return (list);
}

char	*get_prefilter(char *str, int start, char **new)
{
	char		*filter;
	int			i;
	int			j;

	i = 0;
	while (str[start - i] != ' ' && str[start - i] != '/' && start - i >= 0)
		i++;
	if (!(filter = ft_calloc(i, sizeof(char))))
		return (NULL);
	j = -1;
	while (--i > 0)
		filter[++j] = str[start - i];
	if (!(*new = ft_strchangelen(*new, ft_strlen(*new) - ft_strlen(filter))))
		return (NULL);
	return (filter);
}
