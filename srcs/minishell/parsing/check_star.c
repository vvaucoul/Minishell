/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 22:40:19 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/16 18:55:55 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_linksnum(char *path)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				i;
	char			*finalpath;

	finalpath = ft_strjoin("./", path);
	if ((dirp = opendir(finalpath)) == NULL)
		return (display_error("opendir failed") - 1);
	free(finalpath);
	i = 0;
	while ((dp = readdir(dirp)) != NULL)
		i++;
	closedir(dirp);
	return (i);
}

static void	remove_from_tab(char ***list, int i)
{
	int size;

	size = ft_tablen(list[0]);
	if (i >= size)
		return ;
	free(list[0][i]);
	while (list[0][++i - 1])
		list[0][i - 1] = list[0][i];
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

static char	**get_linkslist(char *path)
{
	char			**list;
	DIR				*dirp;
	struct dirent	*dp;
	int				j;
	char			*finalpath;

	if ((j = get_linksnum(path)) == -1)
		return (NULL);
	if (!(list = malloc(sizeof(char*) * (j + 1))))
		return (NULL);
	list[j] = NULL;
	finalpath = ft_strjoin("./", path);
	if ((dirp = opendir(finalpath)) == NULL)
	{
		display_error("opendir failed");
		return (NULL);
	}
	free(finalpath);
	j = 0;
	while ((dp = readdir(dirp)) != NULL)
	{
		list[j] = ft_strdup(dp->d_name);
		j++;
	}
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
	if (ft_strchangelen(new, ft_strlen(*new) - (ft_strlen(filter))))
		return (NULL);
	return (filter);
}

static char	*get_nextfilter(char *str, int start)
{
	char *filter;
	int i;
	int j;

	i = 0;
	while (str[start + i] && str[start + i] != ' ' && str[start + i] != '*' && str[start + i] != '/')
		i++;
	if (!str[start + i] || str[start + i] == ' ' || str[start + i] != '/')
	{
		// printf("fin1\n");
		i++;
	}
	if (!(filter = ft_calloc(i + 1, sizeof(char))))
		return (NULL);
	if (!str[start + i - 1] || str[start + i - 1] == ' ' ||
		str[start + i - 1] != '/')
	{
		// printf("fin2\n");
		filter[i - 1] = '\n'; //to indicate final filter
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

	// printf("filename : [%s]\n", filename);
	tmp = 0;
	if (ft_strchr(filter, '\n'))
	{
		// printf("fitre de fin\n");
		filter[ft_strlen(filter) - 1] = '\0';
		tmp = 1;
	}
	i = -1;
	while (filename[start + ++i])
	{
		if (tmp && (ft_strlen(filename + (start + i)) != ft_strlen(filter)))
		{
			// printf("pas bon : [%s]\n", filename + (start + i));
			// printf("fitre de fin pas bon\n");
			continue ;
		}
		if (ft_strstartswith(filename + (start + i), filter, 0, 0))
		{
			// printf("filename %lu : [%s]\n", ft_strlen(filename + (start + i)), filename + (start + i));
			// printf("filter   %lu : [%s]\n", ft_strlen(filter), filter);
			return (i);
		}
	}
	return (-1);
}

int			is_dir(const char *path)
{
	struct stat	stat;

	if (lstat(path, &stat) == -1)
		return (-1);
	return (S_ISDIR(stat.st_mode));
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
	if (!(path = ft_calloc(size, sizeof(char))))
		return (NULL);
	j = -1;
	while (++j < size)
		path[j] = str[start - --i];
	// printf("path : [%s]\n", path);
	if (ft_strchangelen(new, ft_strlen(*new) - (ft_strlen(path))))
		return (NULL);
	return (path);
}

char		*get_post_slash(char *str, int start)
{
	char		*post_slash;
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
	if (!(post_slash = ft_calloc(j, sizeof(char))))
		return (NULL);
	j = 0;
	while (str[start + i] && str[start + i] != ' ')
	{
		post_slash[j] = str[start + i];
		i++;
		j++;
	}
	return (post_slash);
}

int			check_star(char **str, t_mns *mns, char **new, int *start)
{
	char		**list;
	char		*prefilter;
	int			i;

	char		*filter;
	// int			filter_len;
	int			j;
	int			k;
	int			l;

	char		*path;
	int			security;
	char		*post_slash;

	(void)mns;
	printf("old input : [%s]\n", *new);
	if (!(post_slash = get_post_slash(*str, *start)))
		return (1);;
	printf("post slash : [%s]\n", post_slash);
	if (!(filter = ft_strdup("")))
		return (1);
	if (!(prefilter = get_prefilter(*str, *start, new)))
		return (1);
	printf("prefilter : [%s]\n", prefilter);
	if (!(path = get_path(*str, *start, new)))
		return (1);
	if (!(list = get_linkslist(path)))
		return (1);
	printf("post init input : [%s]\n", *new);
	security = ft_strlen(*new);
	printf("security : %d\n", security);
	// print_table(list, "table");
	i = ft_tablen(list);
	// printf("i : %d\n", i);
	while (--i >= 0)
	{
		// printf("\t[%s]\n", list[i]);
		if (list[i] && !ft_strstartswith(list[i], prefilter, 0, 0))
		{
			remove_from_tab(&list, i);
			continue ;
		}
		//pseudo code
		j = ft_strlen(prefilter) + 1; // index file
		k = 0; //index str from start
		while (str[0][*start + k + 1] && str[0][*start + k] == '*' && (str[0][*start + k + 1] != ' ' || str[0][*start + k + 1] != '/'))
		{
			k++; //pass *
			// printf("str[0][%d] : [%s]\n", *start +k, str[0] + (*start + k));
			free(filter);
			if (!(filter = get_nextfilter(*str, *start + k)))
				return (1);
			// printf("newfilter = %s\n", filter);
			// printf("%s[%d] : [%s]\n", list[i], j, list[i] + j);
			k += ft_strlen(filter);
			if ((l = contain_filter(list[i], j, filter)) == -1)
			{
				// printf("removed\n");
				remove_from_tab(&list, i);
				// print_table(list, "table");
				break ;
			}
			j += l + 1;
		}
	}
	free(filter);
	free(prefilter);
	// print_table(list, "table");
	// printf("new input : [%s]\n", *new);
	i = 0;
	while (list[i])
	{
		if (i != 0)
			if (!(*new = ft_straddstr(*new, " ", 0)))
				return (1);
		if (!(*new = ft_straddstr(*new, path, 0)))
			return (1);
		if (!(*new = ft_straddstr(*new, list[i], 0)))
			return (1);
		j = ft_strlen(*new);
		if (!(*new = ft_straddstr(*new, post_slash, 0)))
			return (1);
		printf("test1\n");
		while (new[0][j])
		{
			printf("test2\n");
			if (new[0][j] == '*')
			{
				printf("* trouve\n~~~~~~~\n");
				// check_star(str, mns, new, &j); //check for strange j
			}
			j++;
		}
		i++;
	}
	free(path);
	free(post_slash);
	while (new[0][*start] != ' ')
		(*start)++;
	(*start)++;
	// printf("new input : [%s]\n", *new);
	ft_freetab(list);
	return (0);
}
