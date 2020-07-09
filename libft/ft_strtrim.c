/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:38:51 by mle-faou          #+#    #+#             */
/*   Updated: 2019/11/07 12:49:29 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*localstrcpy(char *dest, const char *src)
{
	size_t i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

static int		isinstr(char const c, char const *s)
{
	size_t i;

	i = 0;
	while (s[i])
		if (s[i++] == c)
			return (1);
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && isinstr(s1[start], set))
		start++;
	if (!s1[start])
		return (localstrcpy((char *)ft_calloc(1, sizeof(char)), ""));
	i = start - 1;
	while (s1[++i])
		end = isinstr(s1[i], set) ? end : i;
	if (!(res = (char *)ft_calloc(1, sizeof(char) * (end - start + 2))))
		return (NULL);
	i = 0;
	while (start <= end)
		res[i++] = s1[start++];
	res[i] = '\0';
	return (res);
}
