/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:38:49 by mle-faou          #+#    #+#             */
/*   Updated: 2019/11/07 11:04:44 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (s1[i] && (unsigned char)s1[i] == (unsigned char)s2[i] && i < n - 1)
		i++;
	if (n == 0)
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
