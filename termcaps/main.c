/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 15:53:04 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/21 20:18:59 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps_bonus.h"

/*
**	Init
*/

int	termios_reset_term()
{
	struct termios	s_term;

	tcgetattr(STDIN_FILENO, &s_term);
	s_term.c_lflag |= (ECHO | ICANON);
	s_term.c_oflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &s_term);
	return (0);
}

int	termios_init()
{
	/*
	struct termios	s_term;

	tcgetattr(STDIN_FILENO, &s_term);
	s_term.c_lflag &= ~(ICANON | ECHO);
	s_term.c_oflag &= ~(OPOST);
	s_term.c_cc[VMIN] = 1;
	s_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &s_term);
	tgetent(NULL, getenv("TERM"));
	*/

	struct termios s_term;

	tcgetattr(STDIN_FILENO, &s_term);
	s_term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &s_term);
	tgetent(NULL, getenv("TERM"));


	printf("termios init successfuly\n");
	return (0);
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


int		get_key()
{
	char	*str_buffer;

	if (!(str_buffer = ft_newstr(MAX_KEY_LEN)))
	return (-1);
	read(0, str_buffer, 1);
	if (str_buffer[0] == START_SPECIAL_CHAR)
	{
		read(0, str_buffer + 1, MAX_KEY_LEN - 1);
	}

	// compare keys

	// History

	if (!(memcmp(str_buffer, KEY_CODE_UP, MAX_KEY_LEN)))
	{
		return (KEY_UP);
		// Up history
	}
	else if (!(memcmp(str_buffer, KEY_CODE_DO, MAX_KEY_LEN)))
	{
		return (KEY_DOWN);
		// Down history
	}

	// Move in line

	else if (!(memcmp(str_buffer, KEY_CODE_RI, MAX_KEY_LEN)))
	{
		return (KEY_RIGHT);
		// Right
	}
	else if (!(memcmp(str_buffer, KEY_CODE_LE, MAX_KEY_LEN)))
	{
		return (KEY_LEFT);
		// Left
	}

	// home | end

	else if (!(memcmp(str_buffer, KEY_CODE_HOME, MAX_KEY_LEN)))
	{
		return (KEY_HOME);
		// home (start line)
	}
	else if (!(memcmp(str_buffer, KEY_CODE_END, MAX_KEY_LEN)))
	{
		return (KEY_END);
		// end line
	}

	return (str_buffer[0]);
}

void 	tmp_prompt()
{
	write(0, "$> ", PROMPT_LEN);
}

void 	term_get_line()
{
	t_line	*line;
	int		key_pressed;

	line = init_new_line();
	signal(SIGINT, sig_handler);
	tmp_prompt();
	while (1)
	{
		key_pressed = get_key();

		if (key_pressed >= 32 && key_pressed <= 126)
		insert_char(line, key_pressed);
		else if (key_pressed == KEY_DC || key_pressed == 127)
		delete_char(line, key_pressed);

		else if (key_pressed == KEY_LEFT)
		cursor_to_left(line);
		else if (key_pressed == KEY_RIGHT)
		cursor_to_right(line);

		else if (key_pressed == KEY_HOME)
		cursor_to_start(line);
		else if (key_pressed == KEY_END)
		cursor_to_end(line);

		else if (key_pressed == KEY_UP)
		history_manager(line, 1);
		else if (key_pressed == KEY_DOWN)
		history_manager(line, 0);

		else if (key_pressed == KEY_CTRLL)
		{
			tputs(tgoto(tgetstr("SF", NULL), 0, line->start.row - 1)
			, 1, &term_putchar);
			line->start.row = 1;
			set_curpos(line);
		}
		else if (key_pressed == '\n')
		{
			//insert_char(line, key_pressed);
			printf("\ncmd line [%s]\n", line->cmd);
			add_in_history(line->cmd);
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
	create_history_file();

	// interrogate terminal

	// char *cl_str = tgetstr("cl", NULL);
	// char *cm_str = tgetstr("cm", NULL);
	// t_size size;
	// size.row = tgetnum ("li");
	// size.col = tgetnum ("co");

	//tgetstr ("im", NULL);
	//tgetflag("5i");

	// execute

	while (1)
	{
		term_get_line();
	}

	// End

	termios_reset_term();
	return 0;
}
