/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrange.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 19:14:43 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/10/31 16:50:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strrange(const char *str, const char *list)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!((ft_strchr(list, str[i]))))
			return (1);
		++i;
	}
	return (0);
}
