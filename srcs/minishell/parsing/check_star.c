/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 22:40:19 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/13 22:56:19 by mle-faou         ###   ########.fr       */
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

int			check_star(char **str, t_mns *mns, char **new, int *i)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			**list;
	int				j;

	//get beginning
	//don't forget to add a fun to not add char if followed by a *

	if ((j = get_linksnum()) == -1)
		return (1);
	if (!(list = malloc(sizeof(char*) * (j + 1))))
		return (1);
	list[j] = NULL;
	if ((dirp = opendir(".")) == NULL)
		return (display_error("opendir failed") + 1);
	j = 0;
	while ((dp = readdir(dirp)) != NULL)
	{
		list[j] = ft_strdup(dp->d_name);
		j++;
	}
	closedir(dirp);

	print_table(list, "links");

	return (0);
}

int		is_starfollowed(char *str, int i)
{
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '*')
			return (1);
	}
	return (0);
}