/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 15:53:04 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/04 09:57:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

void		tmp_prompt(void)
{
	write(0, "$> ", 3);
}

void		term_get_line(void)
{
	t_line	*line;
	int		key_pressed;

	line = init_new_line();
	termcaps_update_prompt_len("$> ", 0, FALSE);
	signal(SIGINT, sig_handler);
	tmp_prompt();
	while (1)
	{
		key_pressed = get_key();
		if (!(cmp_keys(line, key_pressed)))
			break ;
	}
	ft_putstr_fd("\n", 0);
}

/*
**	Main
*/

int			main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	termcaps_init();
	term_get_info();
	termios_init();
	while (1)
		term_get_line();
	return (0);
}
