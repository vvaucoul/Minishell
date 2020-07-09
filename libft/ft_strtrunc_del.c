/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrunc_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 23:10:16 by vintz             #+#    #+#             */
/*   Updated: 2020/07/08 19:41:06 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrunc_del(char *s1, char del)
{
	char	*str;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != del)
		++i;
	if (!(str = malloc(sizeof(char) * i + 2)))
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != del)
	{
		str[i] = s1[i];
		++i;
	}
	str[i] = '\0';
	return (str);
}
