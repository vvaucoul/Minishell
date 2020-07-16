/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 15:53:04 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/16 18:57:47 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

/*
**	Init
*/

int	exit_error(char *str)
{
	write (1, str, strlen(str)); // function
	exit(EXIT_FAILURE);
}

void term_get_info()
{
	get_term_struct()->term_size.row = tgetnum("li");
	get_term_struct()->term_size.col = tgetnum("co");
	printf("term has [%d] lines\n", get_term_struct()->term_size.row);
	printf("term has [%d] columns\n", get_term_struct()->term_size.col);
}

int	termcaps_init()
{
	int ret;
	get_term_struct()->term_type = getenv("TERM");
	printf("term type : %s\n", get_term_struct()->term_type);
	ret = tgetent(NULL, get_term_struct()->term_type);
	printf("ret : %d\n", ret);
	if (ret == -1)
	exit_error("la base de données n’est pas accessible.");
	if (ret == 0)
	exit_error("la base de données est accessible mais elle ne contient pas d’info pour ce type de terminal ou trop peu pour fonctionner convenablement.");
	setupterm(get_term_struct()->term_type, 1, NULL);
	return (0);
}

/*
**	Read
*/

void 	term_get_line()
{
	char	buff;
	char	*line;
	int		i;

	while (1)
	{
		tputs(tgetstr("do", NULL), 1, putchar);
		usleep(50000);
		/*
		buff = 0;
		i = 0;
		line = calloc(2048, sizeof(char));
		while (buff != '\n')
		{
			read(1, &buff, 1);
			if (buff != '\n')
			line[i] = buff;
			tputs(tgetstr("dm", NULL), 1, putchar);
			++i;
		}
		printf("line = [%s]\n", line);
		*/
	}
}

/*
** Utils
*/

t_term	*get_term_struct()
{
	static t_term	term;

	return (&term);
}

int		tc_putc(int c)
{
	return (write(0, &c, 1));
}

/*
**	Main
*/

int main(int argc, char **argv)
{
	termcaps_init();
	term_get_info();

	// interrogate terminal

	char *cl_str = tgetstr("cl", NULL);
	char *cm_str = tgetstr("cm", NULL);
	int	auto_wrap = tgetflag("am");
	t_size size;
	size.row = tgetnum ("li");
	size.col = tgetnum ("co");

	char *fill_char = tgetstr ("pc", NULL);

	char *up = tgetstr ("up", NULL);
	char *left = tgetstr ("le", NULL);
	char *right = tgetstr ("ri", NULL);
	char *down = tgetstr ("do", NULL);

	char *k_up = tgetstr ("ku", NULL);

	tgetstr ("im", NULL);

	tgetflag("5i");

	// read

	term_get_line();
	return 0;
}
