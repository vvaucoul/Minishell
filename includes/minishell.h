/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 18:03:44 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/01 15:48:25 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>

#include <stdio.h>
#include <string.h>
#include "libft.h"
#include "libft_up.h"

#define PROMPT_STRING "$> "
#define MAX_CHAR_IN_PROMPT	4096

#define ENV_DELIMITEUR '='

typedef int T_BOOL;
#define TRUE 1
#define FALSE 0

/*
**	COLORS
*/

# define COLOR_NOC         "\033[0m"
# define COLOR_BOLD        "\033[1m"
# define COLOR_UNDERLINE   "\033[4m"
# define COLOR_BLACK       "\033[1;30m"
# define COLOR_RED         "\033[1;31m"
# define COLOR_GREEN       "\033[1;32m"
# define COLOR_YELLOW      "\033[1;33m"
# define COLOR_BLUE        "\033[1;34m"
# define COLOR_VIOLET      "\033[1;35m"
# define COLOR_CYAN        "\033[1;36m"
# define COLOR_WHITE       "\033[1;37m"

typedef struct	s_mns
{
	T_BOOL		is_running;
	char		**envp;
}				t_mns;

/*
**	MINISHELL FUNCTIONS
*/

int		minishell(t_mns *mns);
int   	*parse_arguments(char **args);

/*
**	BUILTINS Functions
*/

T_BOOL		b_isvalid(char *str);

int		b_echo(char **tab, T_BOOL has_argument);

int		b_cd(t_mns *mns, char *path);

int		b_pwd(char **envp, T_BOOL using_nl);
int		b_exit();

int		b_env(char **envp);
int		b_export(t_mns *mns, char **tab);
int		b_unset(char **tab, char **envp);

/*
**	Execve
*/

int		run(t_mns *mns, char *path, char **args, char **envp);
/*
RUN :
- path = /bin/ls
- args[0] = ls
- args[1] = -l
- args[2] = etc...
*/

int		exec(char **tab, char **envp);

/*
**	ENV Functions
*/

char	*get_env_value(char *value, char **envp);

/*
** SIGNAUX
*/

int		init_signals_handle();

/*
**	REDIRECTIONS
*/

int		main_redirections(char *cmd, char **tab, char **envp);
int		r_get_redirection_pos(char **tab);
T_BOOL	r_is_redirection(char *str);
char	**r_get_tab_without_redirection(char **tab);

int		p_pipe(char *cmd, char **tab, char **envp);
char	**r_get_tab_without_pipe(char **tab);

/*
**	TODO
*/

/*
[V] echo et l’option ’-n’
[V] cd uniquement avec un chemin absolu ou relatif
[V] pwd sans aucune option
[V] export sans aucune option
[X] unset sans aucune option			(reste a checker les caracteres)
[V] env sans aucune option ni argument
[V] exit sans aucune option

[V] execve
*/

/*
SIGNAUX:

[V] CTRL + C = SIGINT
[V] CTRL + \ = SIGQUIT
[X] CTRL + D n'est pas un signal mais un EOF

[X] Ne pas afficher les catch (^C ^D ^\)
*/

/*
REDIRECTIONS:

[V] >
[V] >>
[X] <
[X] |

*/

#endif
