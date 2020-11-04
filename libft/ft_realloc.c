/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 15:18:22 by mle-faou          #+#    #+#             */
/*   Updated: 2020/10/08 13:15:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *ptr, size_t size)
{
	char	*new_ptr;
	int		i;

	if (!ptr)
	{
		if (!(new_ptr = ft_calloc(size + 1, sizeof(char))))
			return (NULL);
	}
	else
	{
		if (!(new_ptr = ft_calloc(size + 1, sizeof(char))))
			return (NULL);
		i = 0;
		while (ptr[i])
		{
			new_ptr[i] = ptr[i];
			++i;
		}
		new_ptr[i] = '\0';
		free(ptr);
	}
	return (new_ptr);
}
