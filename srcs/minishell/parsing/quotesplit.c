/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotesplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:55:23 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/10 16:31:41 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		get_size(char *str, char c)
{
	unsigned int	i;
	int				size;

	i = 0;
	size = 0;
	while (str[i])
	{
		while (str[i] == c)
		i++;
		if (!str[i])
			return (size);
		while (str[i] && (str[i] != c || is_in_quotes(str, i)))
			i++;
		size++;
	}
	return (size);
}

char			**quotesplit(char *str, char c)
{
	char	**res;
	int		start;
	int		end;
	int		i;

	int		size;
	size = get_size(str, c);
	if (!(res = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	res[size] = NULL;
	start = 0;
	end = 0;
	i = 0;
	while (i < size)
	{
		while (str[start] == c)
			start++;
		if (!str[start])
			return (res);
		end = start;
		while (str[end] && (str[end] != c || is_in_quotes(str, end)))
			end++;
		res[i] = ft_substr(str, start, (end - start));
		start = end;
		i++;
	}
	return (res);
}
