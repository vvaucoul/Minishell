/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:07:13 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/22 20:42:40 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_BONUS
# define TERMCAPS_BONUS


/*
** Includes
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>

#include "libft.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <curses.h>
#include <termios.h>
#include <term.h>

# define KEY_CODE_UP "\x1b\x5b\x41\0"
# define KEY_CODE_DO "\x1b\x5b\x42\0"
# define KEY_CODE_RI "\x1b\x5b\x43\0"
# define KEY_CODE_LE "\x1b\x5b\x44\0"

# define KEY_CODE_DEL "\x1b\x5b\x33\x7e"

# define KEY_CODE_HOME "\x1b\x5b\x48\0"
# define KEY_CODE_END "\x1b\x5b\x46\0"

# define KEY_CODE_SUP "\x1b\x1b\x5b\x41"
# define KEY_CODE_SDO "\x1b\x1b\x5b\x42"
# define KEY_CODE_SRI "\x1b\x1b\x5b\x43"
# define KEY_CODE_SLE "\x1b\x1b\x5b\x44"

# define KEY_CODE_SHIFT_LEFT "\x1b\x32\x44\x3b\0"
# define KEY_CODE_SHIFT_RIGHT "\x1b\x32\x43\x3b\0"


// key code copier coller, a definir avec matthieu

# define KEY_CODE_COPY_FROM_START "\x1b\x32\x41\x3b\0"
# define KEY_CODE_COPY_FROM_END "\x1b\x32\x42\x3b\0"
# define KEY_CODE_COPY_LINE "0x9"
# define KEY_CODE_PASTE "\x1b\x5b\x5a\0"


# define START_SPECIAL_CHAR '\x1b'
# define START_SHIFT_CHAR '\x31'

# define KEY_CTRLL 12
# define KEY_SHIFT 27

# define TERM_KEY_RIGHT '^[[C'

# define MAX_KEY_LEN 4
# define ADD_KEY_SHIFT_LEN 2
# define MAX_LINE_LEN 4096

# define PROMPT_LEN 3

# define HIST_FILE_NAME ".minishell_history.hist"

// tmp

typedef int T_BOOL;
#define TRUE 1
#define FALSE 0

typedef struct s_size
{
	int row;
	int	col;
}				t_size;

typedef	struct	s_line
{
	t_size		start;
	int			cursor_position;
	int			len;
	char		cmd[MAX_LINE_LEN];
}				t_line;

typedef struct s_term
{
	t_size	term_size;
	char	*term_type;
}				t_term;

/*
**	Function
*/

t_term	*get_term_struct();
int		tc_putc(int c);
int		termios_reset_term();

// utils

int		exit_error(char *str);
void 	sig_handler(int signal);
char	*ft_newstr(int size);
int		term_putchar(int c);

// Line utils

int		line_shift_right(t_line *line);
int		line_shift_left(t_line *line);

// Line

t_line	*init_new_line();
void 	init_line_position(t_line *line);
void	insert_char(t_line *line, int key_pressed);
void	delete_char(t_line *line, int key_pressed);
void	ft_putstr_fd(char const *s, int fd);
void 	delete_full_line(t_line *line);
void 	insert_full_line(t_line *line, char *str);

// cursor

void	set_curpos(t_line *line);
void	cursor_to_end(t_line *line);
void	cursor_to_start(t_line *line);
void	cursor_to_left(t_line *line);
void	cursor_to_right(t_line *line);

// History

int		add_in_history(char *str);
int		history_manager(t_line *line, int up_down, int reset);

// Shift word

int		shift_word_left(t_line *line);
int		shift_word_right(t_line *line);


#endif
