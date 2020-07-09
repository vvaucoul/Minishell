/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:38:03 by mle-faou          #+#    #+#             */
/*   Updated: 2019/11/26 12:06:17 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_swap(char *s)
{
	int		start;
	int		end;
	char	tmp;

	start = 0;
	if (s[0] == '-')
		start++;
	end = ft_strlen(s) - 1;
	tmp = 0;
	while (end > start)
	{
		tmp = s[start];
		s[start] = s[end];
		s[end] = tmp;
		end--;
		start++;
	}
	return (s);
}

char		*ft_itoa(int n)
{
	char		*res;
	int			i;
	long int	nbr;

	nbr = n;
	res = (char*)malloc(sizeof(char) * 12);
	if (res == 0)
		return (0);
	i = 0;
	if (nbr < 0)
	{
		res[i] = '-';
		nbr = -nbr;
		i++;
	}
	if (nbr == 0)
		res[i++] = 48;
	while (nbr >= 1)
	{
		res[i] = (nbr % 10) + 48;
		nbr = nbr / 10;
		i++;
	}
	res[i] = '\0';
	return (ft_swap(res));
}
