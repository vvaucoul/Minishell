/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_star_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 22:40:19 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/03 20:01:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_nextfilter(char *str, int start)
{
	char		*filter;
	int			i;
	int			j;

	i = 0;
	while (str[start + i] && str[start + i] != ' '
		&& str[start + i] != '*' && str[start + i] != '/')
		i++;
	if (!str[start + i] || str[start + i] == ' ' || str[start + i] != '/')
		i++;
	if (!(filter = ft_calloc(i + 1, sizeof(char))))
		return (NULL);
	if (!str[start + i - 1] || str[start + i - 1] == ' ' ||
		(str[start + i - 1] != '/' && (i - 1 > 0)))
	{
		filter[i - 1] = '\n';
		i--;
	}
	j = -1;
	while (++j < i)
		filter[j] = str[start + j];
	return (filter);
}

int			contain_filter(char *filename, int start, char *filter)
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
			break ;
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
	if (!(*new = ft_strchangelen(*new, ft_strlen(*new) - ft_strlen(path))))
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

int			check_file_for_filter(t_starinfo *starinfo, int i, int *j,
char **str)
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
