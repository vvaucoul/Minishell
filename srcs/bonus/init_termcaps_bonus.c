/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:48:04 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/14 18:46:28 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <curses.h>
#include <term.h>


char *tgetstr ();






static struct termios	*get_term(void)
{
	static struct termios term;

	return (&term);
}

int get_term_info ()
{
	char *cl_string, *cm_string;
	int height;
	int width;
	int auto_wrap;
	char PC;
	char *BC;
	char *UP;

	#ifdef Unix

	char *buffer = (char *) malloc (strlen (term_buffer));
	#define BUFFADDR &buffer
	#else
	#define BUFFADDR 0
	#endif

	char *temp;

	/* Extract information we will use.  */
	cl_string = tgetstr ("cl", BUFFADDR);
	cm_string = tgetstr ("cm", BUFFADDR);
	auto_wrap = tgetflag ("am");
	height = tgetnum ("li");
	width = tgetnum ("co");

	printf("cl_string = %s\n", cl_string);
	printf("cm_string = %s\n", cm_string);
	printf("auto_wrap = %d\n", auto_wrap);
	printf("height = %d\n", height);
	printf("width = %d\n", width);

	/* Extract information that termcap functions use.  */
	temp = tgetstr ("pc", BUFFADDR);
	PC = temp ? *temp : 0;
	BC = tgetstr ("le", BUFFADDR);
	UP = tgetstr ("up", BUFFADDR);
	return (0);
}

int	init_termcaps(t_mns *mns)
{
	struct termios	term;
	int		ret;

	if (!(mns->term = malloc(sizeof(t_term))))
	return (-1);

	if (!(mns->term->term_type = getenv("TERM")) || tgetent(NULL, mns->term->term_type) == ERR || (tcgetattr(0, &term) == -1))
	{
		free(mns->term->term_type);
		ft_putstr_fd("Termcaps need a variable \"TERM\" to load\n", 1);
		exit(EXIT_FAILURE);
	}

	if (!(ret = tgetent(mns->term->term_buffer, mns->term->term_type)))
	{
		display_error("la base de donnée ne contient pas assez d'info pour fonctionner correctement");
		return (-1);
	}
	else if (ret == -1)
	{
		display_error("la base de donnée n'est pas accessible'");
		return (-1);
	}
	ft_memcpy(get_term(), &term, sizeof(struct termios));

	/*

	// a activer quand le parseur termcap sera fait

	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	*/


	if (tcsetattr(0, TCSADRAIN, &term) == -1)
	{
		free(mns->term->term_buffer);
		ft_putstr_fd("Quit Termcaps", 1);
		exit(EXIT_FAILURE);
	}
	printf(MNS_COLOR_YELLOW);
	printf("\n\nINIT TermCaps\n");
	printf("termbuffer = %s\n\n", mns->term->term_type);
	printf(MNS_COLOR_NOC);

	//get_term_info();

	return(0);
}

void 			close_termcaps()
{
	if (tcsetattr(0, 0, get_term()) == -1)
	{
		ft_putstr_fd("Quit Termcaps", 1);
		exit(EXIT_FAILURE);
	}
}
