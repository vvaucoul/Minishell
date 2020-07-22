/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:38:38 by mle-faou          #+#    #+#             */
/*   Updated: 2019/11/07 11:01:00 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recursive(unsigned int n, int *fd)
{
	if (n >= 10)
		recursive(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', *fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		recursive(-n, &fd);
	}
	else
		recursive(n, &fd);
}
