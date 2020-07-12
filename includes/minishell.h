/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:10:28 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/07/12 12:49:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

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

/*
** LIBS Includes
*/
#include "libft.h"

/*
**	Debug/TMP Includes
*/

#include <string.h>
#include <stdio.h>
#include <termios.h>

/*
**	Bonus Includes
*/

// #include <curses.h>
// #include <term.h>

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

/*
**	Utils Defines
*/

typedef int T_BOOL;
#define TRUE 1
#define FALSE 0

#define MAX_CHAR_IN_PROMPT 4096
#define ENV_DELIMITEUR '='
#define ENV_STRING_DELIMITEUR "="

/*
**	Main Struct
*/

typedef struct	s_mns
{
	char		**envp;
	int			last_return;
}				t_mns;

/*
**	Functions Definitions
*/

/*
**	Minishell
*/

int				minishell(t_mns *mns);

/*
**	Exec
*/

int				exec_input(char **commands, t_mns *mns);
int				exec_command(char *line, t_mns *mns);
int				exec_builtins(char **command, t_mns *mns);
int				exec_system(char **command, t_mns *mns);
int				run(t_mns *mns, char *path, char **args, char **envp);
int				exec(char **tab, char **envp);

char			**get_sysbin_loc(char **envp);

/*
**	Parsing
*/

char			*check_homedollar(char **str, t_mns *mns);
char			**quotesplit(char *str, char c);
int				*parse_arguments(char **args);

/*
**	Input
*/

int				get_input(char **input, t_mns *mns);

/*
**	Utils
*/

void			exit_shell(void);
int				is_in_quotes(char *str, int pos);
char			*epur_b_str(char *str);
int				display_error(char *str);
int				display_error_cmd(char *str);
int				print_table(char **tab, char *str);
T_BOOL			tab_has_redirection(char **tab);
T_BOOL			tab_has_pipe(char **tab);
char			**r_update_pipe_tab(char **tab, char **envp);
int				tab_len(char **tab);
char 			**add_default_flag(char **tab);

/*
**	Utils Builtins
*/

char			*get_cmd_in_path(char *path);
char			**remove_builtin_in_tab(char **tab);
T_BOOL			b_isvalid(char *str);

/*
**	Utils Envp
*/

char			*get_env_var(char **envp, char *to_find, int free_to_find);
char			*get_env_name(char *str, int i);
char			*get_env_value(char *value, char **envp);

/*
**	Builtins
*/

int				b_echo(char **tab);
int				b_cd(t_mns *mns, char *path);
int				b_pwd(t_mns *mns, T_BOOL using_nl);
int				b_exit();
int				b_env(t_mns *mns);
int				b_export(t_mns *mns, char **tab);
int				b_unset(char **tab, char **envp);

/*
**	Redirections
*/

T_BOOL			r_is_redirection(char *str);
int				p_pipe(char **tab, char **envp);
char			**r_get_tab_without_redirection(char **tab);
int				r_get_redirection_pos(char **tab);
int				main_redirections(char **tab, char **envp);
char			**r_get_tab_before_redirection(char **tab);
char			**r_get_tab_after_redirection(char **tab);

/*
**	Signaux
*/

int				init_signals_handle();
void 			reset_signals();

#endif
