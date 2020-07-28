/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 15:53:04 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/28 17:56:46 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

void 	tmp_prompt()
{
	write(0, "$> ", PROMPT_LEN);
}

void 	term_get_line()
{
	t_line	*line;
	T_BOOL	use_multilines;
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
	}
}

/*
**	Main
*/

int main(int argc, char **argv)
{
	termcaps_init();
	term_get_info();
	termios_init();
	while (1)
		term_get_line();
	termios_reset_term();
	return 0;
}
