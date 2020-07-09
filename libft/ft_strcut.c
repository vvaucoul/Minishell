/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:39:51 by mle-faou          #+#    #+#             */
/*   Updated: 2020/06/30 14:58:29 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char		*ft_strcut(const char *str, char c)
{
	int		i;
	int		j;
	char	*ptr;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == '\0')
		return (NULL);
	i++;
	j = 0;
	while (str[i + j])
		j++;
	if (!(ptr = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	ptr[j] = '\0';
	j = 0;
	while (str[i + j])
	{
		ptr[j] = str[i + j];
		j++;
	}
	return (ptr);
}
