/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:07:13 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/16 15:52:46 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_BONUS
# define TERMCAPS_BONUS

#include <curses.h>
#include <term.h>

#define ANSWER_LEN	20

# define MAX_KEY_LEN 4

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

# define KEY_CTRLL 12

typedef struct	s_size
{
	int	row;
	int	col;
}				t_size;

typedef struct	s_line
{
	int			cursor;
	int			length;
	int			hist_depth;
	int			hist_size;
	t_size		winsz;
	t_size		start;
	char		cmd[MAX_CHAR_IN_PROMPT];
}				t_line;

typedef struct	s_term
{
	char	*term_type;
	char	term_buffer[2048];
	t_size	term_size;
}				t_term;


t_term			*init_termcaps(t_mns *mns);
void			termcaps_mode_default();
void			termcaps_mode_raw();
int				termcaps_get_input(t_line *line, t_mns *mns);
void 			close_termcaps();
void			termcaps_get_cursor_start_pos(t_line *line);

#endif
