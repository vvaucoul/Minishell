/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 22:40:19 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/14 14:49:39 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_linksnum(void)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				i;

	if ((dirp = opendir(".")) == NULL)
		return (display_error("opendir failed") - 1);
	while ((dp = readdir(dirp)) != NULL)
		i++;
	closedir(dirp);
	return (i);
}

char		**get_linkslist()
{
	char			**list;
	DIR				*dirp;
	struct dirent	*dp;
	int				j;

	if ((j = get_linksnum()) == -1)
		return (NULL);
	if (!(list = malloc(sizeof(char*) * (j + 1))))
		return (NULL);
	list[j] = NULL;
	if ((dirp = opendir(".")) == NULL)
	{
		display_error("opendir failed");
		return (NULL);
	}
	j = 0;
	while ((dp = readdir(dirp)) != NULL)
	{
		list[j] = ft_strdup(dp->d_name);
		j++;
	}
	closedir(dirp);
	return (list);
}

char		*get_prefilter(char *str, int start, char **new)
{
	char *filter;
	int i;
	int j;

	i = 0;
	while (str[start - i] != ' ' && start - i >= 0)
		i++;
	if (!(filter = malloc(sizeof(char) * i)))
		return (NULL);
	filter[i] = '\0';
	j = 0;
	while (--i > 0)
	{
		filter[j] = str[start - i];
		j++;
	}
	if (ft_strchangelen(new, ft_strlen(*new) - ft_strlen(filter)))
		return (NULL);
	return (filter);
}

void		remove_from_tab(char ***list, int i)
{
	int size;

	size = ft_tablen(*list);
	if (size >= i)
		return ;
	// while (*list[i])
	// {

	// }

	return ;
}

int			check_star(char **str, t_mns *mns, char **new, int *i)
{
	char		**list;
	char		*filter;
	int			j;

	//get beginning from * , cut fun
	//continue until ' '

	if (!(filter = get_prefilter(*str, *i, new)))
		return (-1);
	list = get_linkslist();
	print_table(list, "links");
	j = 0;
	while (list[j])
	{

		j++;
	}

	return (0);
}
