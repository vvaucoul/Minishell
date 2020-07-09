/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:05:16 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/08 19:34:03 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_straddstr(char *s1, char *s2, int free_s2)
{
	int i;
	int j;
	int k;
	char *new;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(new = ft_realloc(s1, i + j + 1)))
		return (NULL);
	k = -1;
	while (++k < j)
		new[i + k] = s2[k];
	if (free_s2)
		free(s2);
	new[i + j] = '\0';
	return (new);
}
