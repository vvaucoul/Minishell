/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchangelen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 14:08:37 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/14 14:26:39 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strchangelen(char **ptr, size_t size)
{
	char	*new_ptr;
	int		i;

	if (!(new_ptr = ft_calloc(size + 1, (sizeof(char)))))
		return (1);
	if (ptr[0])
	{
		i = 0;
		while (ptr[0][i] && (size_t)i < size)
		{
			new_ptr[i] = ptr[0][i];
			i++;
		}
		free(ptr[0]);
	}
	ptr[0] = new_ptr;
	return (0);
}