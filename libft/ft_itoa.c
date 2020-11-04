/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:38:03 by mle-faou          #+#    #+#             */
/*   Updated: 2020/10/15 16:10:42 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		n_lenght(int n)
{
	int nsize;

	nsize = 0;
	if (n > -2147483648 && n < 0)
	{
		++nsize;
		n *= -1;
	}
	else if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (11);
	while (n >= 1)
	{
		n /= 10;
		++nsize;
	}
	return (nsize);
}

static int		is_min_int(int n, char **str)
{
	if (n != -2147483648)
		return (0);
	free(*str);
	*str = ft_strdup("-2147483648");
	return (1);
}

char			*ft_itoa(int n)
{
	int		i;
	int		size;
	char	*str;
	int		isneg;

	size = n_lenght(n);
	if ((str = malloc(sizeof(char) * (n_lenght(n) + 1))) == NULL)
		return (NULL);
	if (is_min_int(n, &str) == 1)
		return (str);
	if ((isneg = ((n > -2147483648 && n < 0) ? 1 : 0)) == 1)
		n *= -1;
	i = (isneg ? 1 : 1);
	while (size - i >= 0)
	{
		str[size - i] = n % 10 + 48;
		n /= 10;
		++i;
	}
	if (isneg)
		str[0] = '-';
	str[size] = '\0';
	return (str);
}
