/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:38:54 by mle-faou          #+#    #+#             */
/*   Updated: 2020/10/06 11:22:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		if (!(res = ft_calloc(1, sizeof(char))))
			return (NULL);
	}
	else
	{
		if (!(res = ft_calloc(len + 1, sizeof(char))))
			return (NULL);
		i = 0;
		while (i < len)
			res[i++] = s[start++];
	}
	return (res);
}
