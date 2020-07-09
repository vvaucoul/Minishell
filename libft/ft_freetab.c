/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 15:32:06 by mle-faou          #+#    #+#             */
/*   Updated: 2020/07/08 14:21:42 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freetab(char **array)
{
	int i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
	{
		free(array[i]);
	}
	free(array);
	array = NULL;
}
