/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab_onsize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:22:52 by mle-faou          #+#    #+#             */
/*   Updated: 2020/10/15 18:26:57 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freetab_onsize(char **array, int size)
{
	int i;

	if (!array)
		return ;
	i = 0;
	while (i <= size)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}
