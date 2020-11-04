/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:25:08 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/10/21 15:28:49 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

/*
**	Init Termios
*/

int		termios_reset_term(void)
{
	struct termios	s_term;

	tcgetattr(STDIN_FILENO, &s_term);
	s_term.c_lflag |= (ECHO | ICANON);
	s_term.c_oflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &s_term);
	return (0);
}

int		termios_init(void)
{
	struct termios s_term;

	tcgetattr(STDIN_FILENO, &s_term);
	s_term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &s_term);
	tgetent(NULL, getenv("TERM"));
	return (0);
}

void	term_get_info(void)
{
	get_term_struct()->term_size.row = tgetnum("li");
	get_term_struct()->term_size.col = tgetnum("co");
}

int		termcaps_init(void)
{
	int ret;

	get_term_struct()->term_type = getenv("TERM");
	ret = tgetent(NULL, get_term_struct()->term_type);
	if (ret == -1)
		exit_error("la base de données n’est pas accessible.");
	if (ret == 0)
		exit_error("la base de données est accessible mais elle ne contient \
		pas d’info pour ce type de terminal ou trop peu pour fonctionner \
		convenablement.");
	setupterm(get_term_struct()->term_type, 1, NULL);
	return (0);
}
