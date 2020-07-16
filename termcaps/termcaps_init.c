/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:48:04 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/15 17:28:54 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "termcaps_bonus.h"

static struct termios	*get_term(void)
{
	static struct termios term;

	return (&term);
}

t_term	*init_termcaps(t_mns *mns)
{
	static t_term		s_term;
	struct termios		term;
	int					ret;

	if (!(s_term.term_type = getenv("TERM")) || tgetent(NULL, s_term.term_type) == ERR ||
	(tcgetattr(0, &term) == -1))
	{
		free(s_term.term_type);
		ft_putstr_fd("Termcaps need a variable \"TERM\" to load\n", 1);
		exit(EXIT_FAILURE);
	}
	if (!(ret = tgetent(s_term.term_buffer, s_term.term_type)))
	{
		display_error("la base de donnée ne contient pas assez d'info pour fonctionner correctement");
		return (NULL);
	}
	else if (ret == -1)
	{
		display_error("la base de donnée n'est pas accessible'");
		return (NULL);
	}
	ft_memcpy(get_term(), &term, sizeof(struct termios));
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
	{
		free(s_term.term_buffer);
		ft_putstr_fd("Quit Termcaps", 1);
		exit(EXIT_FAILURE);
	}
	s_term.term_size.col = tgetnum("co");
	s_term.term_size.row = tgetnum("li");
	termcaps_mode_raw();
	return(&s_term);
}

void 			close_termcaps()
{
	if (tcsetattr(0, 0, get_term()) == -1)
	{
		ft_putstr_fd("Quit Termcaps", 1);
		exit(EXIT_FAILURE);
	}
}
