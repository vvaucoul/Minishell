/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstartswith.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:43:10 by mle-faou          #+#    #+#             */
/*   Updated: 2020/10/20 15:36:43 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strstartswith(char *s1, char *s2, int free_s1, int free_s2)
{
	int	i;
	int	ret;

	ret = 1;
	i = 0;
	while (s2[i])
	{
		if (!s1[i])
		{
			ret = 0;
			break ;
		}
		if (s1[i] != s2[i])
			ret = 0;
		i++;
	}
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (ret);
}
