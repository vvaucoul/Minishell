/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 15:53:04 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/06 16:47:03 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

void		tmp_prompt(void)
{
	write(0, "$> ", PROMPT_LEN);
}

void		term_get_line(void)
{
	t_line	*line;
	t_bool	use_multilines;
	int		key_pressed;

	line = init_new_line();
	use_multilines = FALSE;
	signal(SIGINT, sig_handler);
	tmp_prompt();
	while (1)
	{
		key_pressed = get_key();
		if (!term_get_multiline(line, &use_multilines, key_pressed))
		{
			if (!(cmp_keys(line, key_pressed)))
				break ;
		}
		else if (use_multilines == 2)
			break ;
	}
}

/*
**	Main
*/

int			main(int argc, char **argv)
{
	termcaps_init();
	term_get_info();
	termios_init();
	term_get_line();
	termios_reset_term();
	system("leaks termcaps");
	return (0);
}
