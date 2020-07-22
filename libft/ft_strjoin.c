/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:38:43 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/07 15:02:37 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	if (!(new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	new[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = i;
	i = -1;
	while (s2[++i])
		new[j + i] = s2[i];
	return (new);
}
