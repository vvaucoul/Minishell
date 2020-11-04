/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:44:20 by mle-faou          #+#    #+#             */
/*   Updated: 2020/10/20 15:35:59 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_straddchar(char *str, char c)
{
	int		i;
	char	*new;

	i = ft_strlen(str);
	if (!(new = ft_realloc(str, i + 2)))
		return (NULL);
	new[i] = c;
	new[i + 1] = '\0';
	return (new);
}
