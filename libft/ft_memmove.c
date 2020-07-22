/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:38:11 by mle-faou          #+#    #+#             */
/*   Updated: 2019/11/07 11:03:18 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	if (!dest && !src)
		return (NULL);
	i = 0;
	ptr_dest = (unsigned char*)dest;
	ptr_src = (unsigned char*)src;
	if (ptr_src < ptr_dest)
		while (++i <= n)
			ptr_dest[n - i] = ptr_src[n - i];
	else
		while (n-- > 0)
			*(ptr_dest++) = *(ptr_src++);
	return (dest);
}
