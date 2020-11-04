/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:05:16 by mle-faou          #+#    #+#             */
/*   Updated: 2020/11/01 18:20:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

char		*ft_straddstr(char *s1, char *s2, int to_free)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(new = ft_calloc(i + j + 1, sizeof(char))))
		return (NULL);
	k = -1;
	while (++k < i)
		new[k] = s1[k];
	k = -1;
	while (++k < j)
		new[i + k] = s2[k];
	if (to_free - 2 >= 0)
	{
		to_free -= 2;
		free(s2);
	}
	if (to_free - 1 >= 0)
		free(s1);
	return (new);
}
