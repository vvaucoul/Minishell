/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 15:53:04 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/22 20:45:08 by vvaucoul         ###   ########.fr       */
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

	if (!(str_buffer = ft_newstr(MAX_KEY_LEN + ADD_KEY_SHIFT_LEN)))
	return (-1);
	read(0, str_buffer, 1);
	if (str_buffer[0] == START_SPECIAL_CHAR)
	{
		read(0, str_buffer + 1, MAX_KEY_LEN - 1);
	}
	if (str_buffer[2] == START_SHIFT_CHAR)
	{
		//printf("read more\n");
		read(0, str_buffer + 1, ADD_KEY_SHIFT_LEN);
	}

	// to display key code
	printf("str_buffer [%p]\n", str_buffer[0]);
	printf("str_buffer [%p]\n", str_buffer[1]);
	printf("str_buffer [%p]\n", str_buffer[2]);
	printf("str_buffer [%p]\n", str_buffer[3]);
	printf("str_buffer [%p]\n", str_buffer[4]);
	printf("str_buffer [%p]\n", str_buffer[5]);

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

	// jump through words

	else if (!(memcmp(str_buffer, KEY_CODE_SHIFT_LEFT, ADD_KEY_SHIFT_LEN + ADD_KEY_SHIFT_LEN)))
	{
		return (KEY_SLEFT);
		// shift left
	}
	else if (!(memcmp(str_buffer, KEY_CODE_SHIFT_RIGHT, MAX_KEY_LEN + ADD_KEY_SHIFT_LEN)))
	{
		return (KEY_SRIGHT);
		// shift right
	}

	// copy paster

	else if (!(memcmp(str_buffer, KEY_CODE_COPY_FROM_START, MAX_KEY_LEN + ADD_KEY_SHIFT_LEN)))
	{
		return (540);
		// scopy from start
	}
	else if (!(memcmp(str_buffer, KEY_CODE_COPY_FROM_END, MAX_KEY_LEN + ADD_KEY_SHIFT_LEN)))
	{
		return (541);
		// copy from end
	}
	//else if (!(memcmp(str_buffer, KEY_CODE_COPY_LINE, MAX_KEY_LEN + ADD_KEY_SHIFT_LEN)))
	// else if (!strcmp(str_buffer[0] ,KEY_CODE_COPY_LINE))
	// {
	// 	return (542);
	// 	// a mediter minutieusement parce que la, flemme
	// }
	else if (!(memcmp(str_buffer, KEY_CODE_PASTE, MAX_KEY_LEN + ADD_KEY_SHIFT_LEN)))
	{
		return (543);
		// paste line
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
		history_manager(line, 1, 0);
		else if (key_pressed == KEY_DOWN)
		history_manager(line, 0, 0);

		// a finir, shift left & right
		else if (key_pressed == KEY_SLEFT)
		shift_word_left(line);
		else if (key_pressed == KEY_SRIGHT)
		shift_word_right(line);

		// tmp, copy paste
		else if (key_pressed == 540)
		exit(0);
		else if (key_pressed == 541)
		exit(0);
		else if (key_pressed == 542)
		exit(0);
		else if (key_pressed == 543)
		exit(0);

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
			history_manager(line, 0, 1);
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

	// execute

	while (1)
	{
		term_get_line();
	}

	// End

	termios_reset_term();
	return 0;
}
