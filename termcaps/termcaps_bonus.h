/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:07:13 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/17 15:42:17 by vvaucoul         ###   ########.fr       */
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

#include <stdio.h>
#include <string.h>

#include <curses.h>
#include <termios.h>
#include <term.h>

#define TERM_MOVE_UP	 	"\033[XA" // Move up X lines;
#define TERM_MOVE_DOWN	 	"\033[XB" // Move down X lines;
#define TERM_MOVE_RIGHT	 	"\033[XC" // Move right X column;
#define TERM_MOVE_LEFT	 	"\033[XD" // Move left X column;
#define TERM_CLEAR_SCREEN	"\033[2J" // Clear screen


# define KEY_CODE_UP "\x1b\x5b\x41\0"
# define KEY_CODE_DO "\x1b\x5b\x42\0"
# define KEY_CODE_RI "\x1b\x5b\x43\0"
# define KEY_CODE_LE "\x1b\x5b\x44\0"

#define TERM_KEY_RIGHT '^[[C'
# define MAX_KEY_LEN 4

typedef struct s_size
{
	int row;
	int	col;
}				t_size;

typedef struct s_term
{
	t_size	term_size;
	char	*term_type;
}				t_term;

/*
**	Function
*/

t_term	*get_term_struct();

#endif
