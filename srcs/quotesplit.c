/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotesplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 18:55:23 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/09 15:44:12 by mle-faou         ###   ########.fr       */
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
		// printf("%d, '%c'\n", i, str[i]);
		// while (str[i] && str[i] != c)
		// 	i++;
		// while (str[i] == c)
		// 	i++;
		// if (str[i] && str[i] != c && !is_in_quotes(str, i))


		while (str[i] == c)
		i++;
		if (!str[i])
			return (size);
		while (str[i] && (str[i] != c || is_in_quotes(str, i)))
			i++;
		size++;
	}
	// printf("size : %d\n", size);
	return (size);
}

// static char		**error(char **res, char *str)
// {
// 	if (!(res[0] = ft_strdup(str)))
// 		return (NULL);
// 	res[1] = 0;
// 	return (res);
// }

char			**quotesplit(char *str, char c)
{
	char	**res;
	int		start;
	int		end;
	int		i;

	int		size;
	size = get_size(str, c);
	printf("size malloced : %d\n", size);

	if (!(res = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	res[size] = NULL;
	if (size == 1)
	{
		res[0] = ft_strdup(str);
		return(res);
	}
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
		// printf("i : %d, c : '%c' %d\n", i, str[end], is_in_quotes(str, end));
		while (str[end] && (str[end] != c || is_in_quotes(str, end)))
			end++;
		res[i] = ft_substr(str, start, (end - start));
		// printf("res[%d] : [%s]\n", i, res[i]);
		start = end;
		i++;
	}

	// printf("split on '%c'\n", c);
	// i = 0;
	// while (res[i])
	// {
	// 	printf("res[%d] : [%s]\n", i, res[i]);
	// 	i++;
	// }
	// printf("done\n");

	return (res);
}
