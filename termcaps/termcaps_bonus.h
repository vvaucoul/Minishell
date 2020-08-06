/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:07:13 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/08/06 18:07:13 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_BONUS_H
# define TERMCAPS_BONUS_H

/*
** Includes
*/

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>

# include "libft.h"

# include <stdio.h>
# include <string.h>
# include <ctype.h>

# include <curses.h>
# include <termios.h>
# include <term.h>

/*
**	Defines
*/

/*
** Key codes Defines (get key from keyboard)
*/

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

# define KEY_CODE_SHIFT_UP		"\x1b\x32\x41\x3b\0"
# define KEY_CODE_SHIFT_DOWN	"\x1b\x32\x42\x3b\0"

/*
** copy cut & paste
** position 1 & 2 : shift + I [shift index]
** copier : shift + C [shift copy]		MODE -> [0]
** couper : shift + X [shift cut]		MODE -> [1]
** coller : shift + V [shift paste]		MODE -> [2]
*/

# define KEY_CODE_INSERT_INDEX "\x49\0"
# define KEY_CODE_COPY "\x43\0"
# define KEY_CODE_CUT "\x58\0"
# define KEY_CODE_PASTE "\x56\0"

# define KEY_INSERT_INDEX 540
# define KEY_CCOPY 541
# define KEY_CUT 542
# define KEY_PASTE 543

# define KEY_SHIFT_UP 544
# define KEY_SHIFT_DOWN 545

# define START_SPECIAL_CHAR '\x1b'
# define START_SHIFT_CHAR '\x31'

# define KEY_CTRLL 12
# define KEY_SHIFT 27

/*
**	DEFINE LINE
*/

# define MAX_KEY_LEN 4
# define ADD_KEY_SHIFT_LEN 2
# define MAX_LINE_LEN 4096

/*
**	DEFINE TERM
*/

# define PROMPT_LEN 3

/*
** DEFINE HISTORY
*/

# define HIST_FILE_NAME ".minishell_history.hist"

/*
**	DEFINE MULTI LINE MANAGER
*/

# define MAX_MULTI_LINE_ROW 	9

# define MLM_NOTHING 			0
# define MLM_UP 				1
# define MLM_DOWN 				2
# define MLM_RESET 				3
# define MLM_ADD_KEY 			4
# define MLM_REMOVE_KEY			5
# define MLM_CM_LEFT 			6
# define MLM_CM_RIGHT 			7
# define MLM_HOME 				8
# define MLM_END 				9
# define MLM_SW_LEFT 			10
# define MLM_SW_RIGHT 			11

/*
** Manager HELPER
** state
** = 0 => do nothing
** = 1 => Up
** = 2 => down
** = 3 => reset
** = 4 => add key
** = 5 => remove key
** = 6 => cursor motion left
** = 7 => cursor motion right
** = 8 => home (start line)
** = 9 => end (end line)
** = 10 => shift word left
** = 11 => shift word right
**	add other things like copy cut paste, clear and other
*/

typedef int	t_bool;
# define TRUE 1
# define FALSE 0

/*
** Termcaps Structs
*/

typedef	struct	s_history
{
	int			hist_len;
	int			actu_hist_line;
}				t_history;

typedef	struct	s_size
{
	int			row;
	int			col;
}				t_size;

typedef	struct	s_line
{
	t_size		start;
	int			cursor_position;
	int			len;
	char		cmd[MAX_LINE_LEN];
	char		copy_cmd[MAX_LINE_LEN];
}				t_line;

typedef	struct	s_term
{
	t_size		term_size;
	char		*term_type;
}				t_term;

/*
**	Function
*/

t_term			*get_term_struct();
int				tc_putc(int c);
int				termios_reset_term();

/*
**	Termios
*/

int				termios_reset_term();
int				termios_init();
void			term_get_info();
int				termcaps_init();

/*
**	utils
*/

int				exit_error(char *str);
void			sig_handler(int signal);
char			*ft_newstr(int size);
int				term_putchar(int c);

/*
**	Read & CMP Keys
*/

int				get_key();
int				cmp_keys(t_line *line, int key_pressed);

/*
** Line utils
*/

int				line_shift_right(t_line *line);
int				line_shift_left(t_line *line);

/*
** Line
*/

t_line			*init_new_line();
void			init_line_position(t_line *line);
void			insert_char(t_line *line, int key_pressed);
void			delete_char(t_line *line, int key_pressed);
void			delete_full_line(t_line *line);
void			insert_full_line(t_line *line, char *str);

/*
** cursor
*/

void			set_curpos(t_line *line);
void			cursor_to_end(t_line *line);
void			cursor_to_start(t_line *line);
void			cursor_to_left(t_line *line);
void			cursor_to_right(t_line *line);

/*
** History
*/

int				add_in_history(char *str);
int				history_manager(t_line *line, int up_down, int reset);
int				history_init(int reset, int *init, int up_down,
t_history *hist);
int				get_last_history_line(void);

/*
** Shift word
*/

int				shift_word_left(t_line *line);
int				shift_word_right(t_line *line);

/*
** copy & paste line
*/

void			copy_paste_manager(t_line *line, t_bool set_index, int mode);

/*
** copy & paste utils
*/

void			reset_copy_line(t_line *line);
void			insert_copy_character(t_line *line, int index, t_bool reset);
t_bool			index_valids(int *index);
void			swap_index(int **index);

/*
** Multi line edition
*/

int				term_get_multiline(t_line *line, t_bool *use_multilines,
int key_pressed);
int				multi_line_manager(t_line *line, char key_pressed, int state);
void			clear_multi_line_cmd(t_line *ml_lines, int y, int max);
void			ml_delete_char(t_line *line, int key_pressed);
void			ml_refresh_lines(t_line *line);
void			convert_multilines_to_line(t_line **ml_lines, t_line *line);
void			insert_char_in_line(t_line **ml_lines, int index,
int key_pressed);
void			delete_char_in_line(t_line **ml_lines, int index,
int key_pressed);

void			ml_cm_left(t_line **ml_lines, int index);
void			ml_cm_right(t_line **ml_lines, int index);
void			ml_cm_start(t_line **ml_lines, int index);
void			ml_cm_end(t_line **ml_lines, int index);

int				mlm_shift_word_left(t_line **ml_lines, int index);
int				mlm_shift_word_right(t_line **ml_lines, int index);

void			display_prompt_line(int line);
void			update_cursor_position(t_size cp);

#endif
