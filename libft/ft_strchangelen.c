/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchangelen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 14:08:37 by mle-faou          #+#    #+#             */
/*   Updated: 2020/10/21 15:40:03 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchangelen(char *str, int size)
{
	char	*new_ptr;
	int		i;

	if (!(new_ptr = ft_calloc(size + 1, (sizeof(char)))))
		return (NULL);
	if (str)
	{
		i = 0;
		while (str[i] && i < size)
		{
			new_ptr[i] = str[i];
			i++;
		}
		free(str);
	}
	return (new_ptr);
}
