/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:42:45 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/20 18:56:34 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

/*
** Utils
*/

void 	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		termios_reset_term();
		exit (0);
	}
}

t_term	*get_term_struct()
{
	static t_term	term;

	return (&term);
}

int	exit_error(char *str)
{
	write (1, str, strlen(str)); // function
	exit(EXIT_FAILURE);
}

char	*ft_newstr(int size)
{
	char	*str;
	int		i;

	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = -1;
	while (i++ <= size)
		str[i] = '\0';
	return (str);
}

int		term_putchar(int c)
{
	return (write(0, &c, 1));
}

void	ft_putstr_fd(char const *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, strlen(s));
}
