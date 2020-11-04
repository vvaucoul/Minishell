/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:44:03 by user42            #+#    #+#             */
/*   Updated: 2020/11/01 18:49:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*star_handler(char **str, int *cancel)
{
	int			i;
	char		*new;
	int			ret;
	int			sum;

	sum = 0;
	if (!(new = ft_strnew(1)))
		return (NULL);
	i = -1;
	while (str[0][++i])
	{
		if (str[0][i] == '*' && !is_in_quotes(str[0], i))
		{
			if ((ret = check_star(str, &new, &i)) == -1)
				return (NULL);
			sum += ret;
		}
		else if (!(new = ft_straddchar(new, str[0][i])))
			return (NULL);
	}
	if (sum == 0)
		*cancel = 1;
	free(*str);
	return (new);
}

static int		contain_star(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' && !is_in_quotes(str, i))
			return (1);
		i++;
	}
	return (0);
}

char			*update_star(char **str)
{
	char		*new;
	int			cancel;

	new = ft_strdup(*str);
	cancel = 0;
	while (contain_star(new))
	{
		if (!(new = star_handler(&new, &cancel)))
			return (NULL);
		if (cancel)
		{
			free(new);
			return (*str);
		}
	}
	free(*str);
	return (new);
}
