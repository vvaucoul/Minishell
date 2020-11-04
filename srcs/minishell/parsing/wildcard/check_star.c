/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 22:40:19 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/03 17:34:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_file_for_prefilter(t_starinfo *starinfo, int i,
	char **str)
{
	int			j;

	if (starinfo->list[i] && !ft_strstartswith(starinfo->list[i],
		starinfo->prefilter, 0, 0))
		return (remove_from_tab(&starinfo->list, i));
	j = ft_strlen(starinfo->prefilter) + 1;
	if (check_file_for_filter(starinfo, i, &j, str))
		return (1);
	return (0);
}

int				update_new(t_starinfo *starinfo, char **new)
{
	int			i;

	i = 0;
	while (starinfo->list[i])
	{
		if (!(*new = ft_straddstr(*new, starinfo->path, 1)))
			return (1);
		if (!(*new = ft_straddstr(*new, starinfo->list[i], 1)))
			return (1);
		if (!(*new = ft_straddstr(*new, starinfo->post, 1)))
			return (1);
		if (!(*new = ft_straddstr(*new, " ", 1)))
			return (1);
		i++;
	}
	return (0);
}

int				init_starinfo(t_starinfo *starinfo, char **str, char **new,
	int *start)
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
	return (0);
}

void			free_starinfo(t_starinfo *starinfo)
{
	free(starinfo->filter);
	free(starinfo->prefilter);
	free(starinfo->path);
	free(starinfo->post);
	ft_freetab(starinfo->list);
}

int				check_star(char **str, char **new, int *start)
{
	t_starinfo	starinfo;
	int			i;

	if (init_starinfo(&starinfo, str, new, start))
		return (-1);
	if (!(starinfo.list = get_linkslist(starinfo.path)))
		return (-1);
	i = ft_tablen(starinfo.list);
	while (--i >= 0)
		if (check_file_for_prefilter(&starinfo, i, str))
			return (-1);
	i = ft_tablen(starinfo.list);
	if (update_new(&starinfo, new))
		return (-1);
	while (str[0][*start] > ' ' && str[0][*start] <= '~')
		(*start)++;
	free_starinfo(&starinfo);
	return (i);
}
