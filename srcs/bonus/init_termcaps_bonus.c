/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:48:04 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/14 17:57:48 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <curses.h>
#include <term.h>
/*
int	init_termcaps()
{
	char	*term_type;
	int		ret;

	term_type = getenv("TERM");
	ret = tgetent(NULL, term_type);

	if (ret == 0)
	{
		display_error("la base de donnée ne contient pas assez d'info pour fonctionner correctement");
		return (-1);
	}
	else if (ret == -1)
	{
		display_error("la base de donnée n'est pas accessible'");
		return (-1);
	}

	return(0);
}
*/
