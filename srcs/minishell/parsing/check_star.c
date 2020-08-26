/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 22:40:19 by mle-faou          #+#    #+#             */
/*   Updated: 2020/08/26 17:38:01 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_linksnum(char *path, int first)
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
		if (first)
		{
			free(finalpath);
			return (display_error("no matches found") -  1);
		}
		return (0);
	}
	free(finalpath);
	i = 0;
	while ((dp = readdir(dirp)) != NULL)
		i++;
	closedir(dirp);
	return (i);
}

static int	remove_from_tab(char ***list, int i)
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

static void	remove_hidden(char ***list)
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

static char	**get_linkslist(char *path, int first)
{
	char			**list;
	DIR				*dirp;
	struct dirent	*dp;
	int				i;
	char			*finalpath;

	if ((i = get_linksnum(path, first)) == -1)
		return (NULL);
	if (!(list = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	list[i] = NULL;
	if (path[0] == '/')
		finalpath = ft_strdup(path);
	else
		finalpath = ft_strjoin("./", path);
	if ((dirp = opendir(finalpath)) == NULL)
		return (list);
	free(finalpath);
	i = 0;
	while ((dp = readdir(dirp)) != NULL)
		list[i++] = ft_strdup(dp->d_name);
	closedir(dirp);
	remove_hidden(&list);
	return (list);
}

static char	*get_prefilter(char *str, int start, char **new)
{
	char *filter;
	int i;
	int j;

	i = 0;
	while (str[start - i] != ' ' && str[start - i] != '/' && start - i >= 0)
		i++;
	if (!(filter = ft_calloc(i, sizeof(char))))
		return (NULL);
	j = -1;
	while (--i > 0)
		filter[++j] = str[start - i];
	if (ft_strchangelen(new, ft_strlen(*new) - ft_strlen(filter)))
		return (NULL);
	return (filter);
}

static char	*get_nextfilter(char *str, int start)
{
	char *filter;
	int i;
	int j;

	i = 0;
	while (str[start + i] && str[start + i] != ' ' 
		&& str[start + i] != '*' && str[start + i] != '/')
		i++;
	if (!str[start + i] || str[start + i] == ' ' || str[start + i] != '/')
		i++;
	if (!(filter = ft_calloc(i + 1, sizeof(char))))
		return (NULL);
	if (!str[start + i - 1] || str[start + i - 1] == ' ' ||
		str[start + i - 1] != '/')
	{
		filter[i - 1] = '\n';
		i--;
	}
	j = -1;
	while (++j < i)
		filter[j] = str[start + j];
	return (filter);
}

static int	contain_filter(char *filename, int start, char *filter)
{
	int			i;
	int			tmp;

	tmp = 0;
	if (ft_strchr(filter, '\n'))
	{
		filter[ft_strlen(filter) - 1] = '\0';
		tmp = 1;
	}
	i = -1;
	while (filename[start + ++i])
	{
		if (tmp && (ft_strlen(filename + (start + i)) != ft_strlen(filter)))
			continue ;
		if (ft_strstartswith(filename + (start + i), filter, 0, 0))
			return (i);
	}
	return (-1);
}

char		*get_path(char *str, int start, char **new)
{
	char		*path;
	int			i;
	int			j;
	int			size;

	i = -1;
	while (start - ++i >= 0)
		if (str[start - i] == '/' || str[start - i] == ' ')
			break;
	if (start - i < 0 || str[start - i] == ' ')
		return (ft_strdup(""));
	size = 0;
	while (str[start - i] != ' ' && start - i >= 0)
	{
		size++;
		i++;
	}
	if (!(path = ft_calloc(size + 1, sizeof(char))))
		return (NULL);
	j = -1;
	while (++j < size)
		path[j] = str[start - --i];
	if (ft_strchangelen(new, ft_strlen(*new) - ft_strlen(path)))
		return (NULL);
	return (path);
}

char		*get_post(char *str, int start)
{
	char		*post;
	int			i;
	int			j;

	i = 0;
	while (str[start + i] && str[start + i] != ' ' && str[start + i] != '/')
		i++;
	if (str[start + i] != '/')
		return (ft_strdup(""));
	j = 0;
	while (str[start + i + j] && str[start + i + j] != ' ')
		j++;
	if (!(post = ft_calloc(j + 1, sizeof(char))))
		return (NULL);
	j = 0;
	while (str[start + i] && str[start + i] != ' ')
	{
		post[j] = str[start + i];
		i++;
		j++;
	}
	return (post);
}

int			check_file_for_filter(t_starinfo *starinfo, int i, int *j, char **str)
{
	int			k;
	int			l;

	k = 0;
	while (str[0][starinfo->start + k + 1] 
		&& str[0][starinfo->start + k] == '*' 
		&& (str[0][starinfo->start + k + 1] != ' ' 
			|| str[0][starinfo->start + k + 1] != '/'))
	{
		k++;
		free(starinfo->filter);
		if (!(starinfo->filter = get_nextfilter(*str, starinfo->start + k)))
			return (1);
		if (ft_strequ(starinfo->filter, "\n"))
			break ;
		k += ft_strlen(starinfo->filter);
		if ((l = contain_filter(starinfo->list[i], *j, starinfo->filter)) == -1)
			return (remove_from_tab(&starinfo->list, i));
		*j += l + 1;
	}
	return (0);
}

int			check_file_for_prefilter(t_starinfo *starinfo, int i, char **str)
{
	int			j;

	if (starinfo->list[i] && !ft_strstartswith(starinfo->list[i], starinfo->prefilter, 0, 0))
		return (remove_from_tab(&starinfo->list, i));
	j = ft_strlen(starinfo->prefilter) + 1;
	if (check_file_for_filter(starinfo, i, &j, str))
		return (1);
	return (0);
}

int			update_new(t_starinfo *starinfo, char **new)
{
	int i;
	int j;

	i = 0;
	while (starinfo->list[i])
	{
		if (i != 0)
			if (!(*new = ft_straddstr(*new, " ", 0)))
				return (1);
		if (!(*new = ft_straddstr(*new, starinfo->path, 0)))
			return (1);
		if (!(*new = ft_straddstr(*new, starinfo->list[i], 0)))
			return (1);
		j = ft_strlen(*new);
		if (!(*new = ft_straddstr(*new, starinfo->post, 0)))
			return (1);
		i++;
	}
	return (0);
}

int		init_starinfo(t_starinfo *starinfo, char **str, char **new, int *start)
{
	starinfo->start = *start;
	if (!(starinfo->post = get_post(*str, *start)))
		return (1);
	if (!(starinfo->filter = ft_strdup("")))
		return (1);
	if (!(starinfo->prefilter = get_prefilter(*str, *start, new)))
		return (1);
	if (!(starinfo->path = get_path(*str, *start, new)))
		return (1);
	return(0);
}

void		free_starinfo(t_starinfo *starinfo)
{
	free(starinfo->filter);
	free(starinfo->prefilter);
	free(starinfo->path);
	free(starinfo->post);
	ft_freetab(starinfo->list);
}

int			check_star(char **str, char **new, int *start, int first)
{
	t_starinfo	starinfo;
	int			i;

	if (init_starinfo(&starinfo, str, new, start))
		return (1);
	if (!(starinfo.list = get_linkslist(starinfo.path, first)))
		return (1);
	i = ft_tablen(starinfo.list);
	while (--i >= 0)
		if (check_file_for_prefilter(&starinfo, i, str))
			return (1);
	if (update_new(&starinfo, new))
		return (1);
	while (str[0][*start] > ' ' && str[0][*start] <= '~')
		(*start)++;
	free_starinfo(&starinfo);
	return (0);
}
