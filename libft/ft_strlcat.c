/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:38:42 by mle-faou          #+#    #+#             */
/*   Updated: 2019/11/07 11:01:08 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	while (dest[++i] && i < size)
		;
	while (src[++j] && i + j + 1 < size)
		dest[i + j] = src[j];
	if (i != size)
		dest[i + j] = '\0';\
	return (i + ft_strlen(src));
}
