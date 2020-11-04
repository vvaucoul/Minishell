/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:10:28 by vvaucoul          #+#    #+#             */
/*   Updated: 2020/11/03 22:40:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

/*
** LIBS Includes
*/

# include "libft.h"
# include "../termcaps/termcaps_bonus.h"

/*
**	Debug/TMP Includes
*/

# include <string.h>
# include <stdio.h>

/*
**	Bonus Includes
*/

# include <curses.h>
# include <termios.h>
# include <term.h>

/*
**	COLORS
*/

# define MNS_COLOR_NOC         "\033[0m"
# define MNS_COLOR_BOLD        "\033[1m"
# define MNS_COLOR_UNDERLINE   "\033[4m"
# define MNS_COLOR_BLACK       "\033[1;30m"
# define MNS_COLOR_RED         "\033[1;31m"
# define MNS_COLOR_GREEN       "\033[1;32m"
# define MNS_COLOR_YELLOW      "\033[1;33m"
# define MNS_COLOR_BLUE        "\033[1;34m"
# define MNS_COLOR_VIOLET      "\033[1;35m"
# define MNS_COLOR_CYAN        "\033[1;36m"
# define MNS_COLOR_WHITE       "\033[1;37m"

/*
**	Utils Defines
*/

typedef int	t_bool;
# define TRUE 1
# define FALSE 0

# define MAX_CHAR_IN_PROMPT 4096
# define ENV_DELIMITEUR '='
# define ENV_JOIN_DELIMITEUR '+'
# define ENV_STRING_DELIMITEUR "="
# define RANDOM_TMP_STRING ".double_redirection"
# define STRNG "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_"

/*
**	TMP
*/

/*
** // Move up X lines;
** // Move down X lines;
** // Move right X column;
** // Move left X column;
** // Clear screen
*/

# define TERM_MOVE_UP	 	"\033[XA"
# define TERM_MOVE_DOWN	 	"\033[XB"
# define TERM_MOVE_RIGHT	"\033[XC"
# define TERM_MOVE_LEFT	 	"\033[XD"
# define TERM_CLEAR_SCREEN	"\033[2J"

# define MNS_EXIT_BAD_ARG   255
# define MNS_DEFAULT_EXIT   0
# define MNS_ERROR			2

# define MNS_FUNC_ERROR		-1
# define MNS_FUNC_SUCCESS	0
# define MNS_B_SUCCESS		1

/*
** Errors
*/

# define E_C		" Too much arguments"
# define E_PS		"Syntax error near to symbol : |"
# define E_SSI		"Shell started in invalid folder"

/*
** -1 ; erreur
**  0 ; nothing
**  1 ; worked
*/

/*
** Bonus struct (operators && || ;)
*/

typedef struct		s_operator
{
	int				operator[MAX_CHAR_IN_PROMPT];
	int				assign_operator;
	int				result_cmd;
}					t_operator;

/*
** Structure pour save les args pour exit mais les free avant (sinon leaks)
*/

typedef struct		s_b_exit
{
	char			**s_args;
	unsigned int	ret;
	t_bool			exit_shell;
}					t_b_exit;

typedef struct		s_pid
{
	pid_t			global_pid;
	int				mns_state;
}					t_pid;

/*
**	Main Struct
*/

typedef struct		s_mns
{
	char			**envp;
	int				last_return;
	t_operator		operator;
	t_b_exit		exit;
	t_bool			use_ctrl_d;
}					t_mns;

/*
**	Functions Definitions
*/

/*
**	Minishell
*/

int					minishell(t_mns *mns);
int					minishell_bonus(t_mns *mns);
void				display_prompt();

/*
**	Exec
*/

int					exec_input(char **commands, t_mns *mns);
int					exec_builtins(char **command, t_mns *mns);
int					exec_system(char **command, t_mns *mns);
int					exec_local_exec(char **command, t_mns *mns);
int					check_specials_cmd(t_mns *mns, char **tabl);
int					run(t_mns *mns, char *path, char **args);
int					exec(char **tabl, t_mns *mns);
int					exec_pipes_redirections(char **command, t_mns *mns);
int					run_cmd(t_mns *mns, char *cmd, char **tabl);
char				**get_sysbin_loc(char **envp);
int					exec_command(char **command, t_mns *mns);
char				*update_star(char **str);

/*
**	Parsing
*/

typedef struct		s_operator_split
{
	char			**splited_str;
	int				i;
	int				j;
	int				k;
}					t_operator_split;

char				**operator_newtab(char **tabl);
int					line_has_operator(char *str);
int					isinstr(char c, char *s);

int					split_operators_valid_char(t_operator_split *op_s,
	char *str);
int					split_operators_op(t_operator_split *op_s, char *str);
char				**split_operators(char *str);

void				reset_mns_operators(t_mns *mns);
int					assign_operators(t_mns *mns, char **new_tab);
char				**clean_operatortab(char **tabl);

char				**append_tab(char **tabl, char **new_tab);
char				**assign_op_tab(char **new_tab, char **tabl);

typedef struct		s_starinfo
{
	int				start;
	char			*post;
	char			*filter;
	char			*prefilter;
	char			*path;
	char			**list;
}					t_starinfo;

typedef struct		s_split
{
	char			**res;
	int				start;
	int				end;
	int				i;
}					t_split;

int					update_input(char **str, t_mns *mns);
char				**quotesplit(char **str, char c, int keep);
char				**str_quotesplit(char *str, char *to_cut, int keep);
char				**ultimate_quotesplit(char *str);
int					lst_cut(t_list **lst, char *to_cut, int keep, int i);
int					lst_split(t_list *lst, char *to_cut, int keep);
t_list				*del_empty(t_list *lst);
int					*parse_arguments(char **args);
char				**operatorsplit(t_mns *mns, char **tabl);
char				**check_semicolon(char **input, t_mns *mns);

/*
** Wildcard *
*/

int					check_star(char **str, char **new, int *i);
int					check_file_for_prefilter(t_starinfo *starinfo, int i,
	char **str);
int					update_new(t_starinfo *starinfo, char **new);
int					init_starinfo(t_starinfo *starinfo, char **str, char **new,
	int *start);
void				free_starinfo(t_starinfo *starinfo);
char				*get_nextfilter(char *str, int start);
int					contain_filter(char *filename, int start, char *filter);
char				*get_path(char *str, int start, char **new);
char				*get_post(char *str, int start);
int					check_file_for_filter(t_starinfo *starinfo, int i, int *j,
	char **str);
int					get_linksnum(char *path);
int					remove_from_tab(char ***list, int i);
void				remove_hidden(char ***list);
char				**get_linkslist(char *path);
char				*get_prefilter(char *str, int start, char **new);

/*
**	Input
*/

int					get_input(t_mns *mns, char **input);

/*
**	Utils
*/

void				exit_shell(void);
int					is_in_quotes(char *str, int pos);
char				*epur_b_str(char *str, t_bool to_free);
int					display_error(char *str);
int					display_errno_error();
int					display_error_cmd(char *str);
int					display_error_arg(char *str, char *cmd);
int					display_malloc_error();
void				display_start_error();
int					display_error_tf(char *str, char *cmd, char *str_bonus,
	int	r_value);
int					display_warning_tf(char *str, char *cmd, char *str_bonus,
	int r_value);
int					print_table(char **tabl, char *str);
void				print_lst(t_list *lst, char *str);
void				test_leaks();
t_bool				tab_has_redirection(char **tabl);
t_bool				tab_has_pipe(char **tabl);
char				**r_update_redirection_tab(char **tabl, char **envp,
	char *redirection);
int					tab_len(char **tabl);
char				**add_default_flag(char **tabl);
int					start_minishell(t_mns *mns, char **envp);
t_bool				ft_stris_digit(char *str);
int					ft_full_tablen(char **tabl);
char				*rm_quotes(char *str);
void				ft_init_to_null(void *str1, void *str2, void *str3,
	void *str4);
t_bool				ft_is_in_range(char *str, int min, int max);
int					ft_intlen(unsigned long long int nb);
char				*ft_strjoin_tf(char *s1, char *s2, int to_free);
void				*disperr_nul(char *str);

/*
** Utils free
*/

void				free_envp(t_mns *mns);
void				multi_free(void *ptr, void *ptr1, void *ptr2, void *ptr3);
void				free_tab(void **ptr);

/*
**	Builtins Utils
*/

int					export_old_path(t_mns *mns, char *old_path);
char				*get_cmd_in_path(char *path);
char				**remove_builtin_in_tab(char **tabl);
t_bool				b_isvalid(char *str);

/*
**	Builtin Export
*/

/*
** // str has =
** // str has +=
** // str already_existing is yes get line else, line = -1
** // key
** // value
*/

typedef struct		s_b_export
{
	t_bool			has_equal;
	t_bool			use_join;
	int				already_existing;
	char			*cmd;
	char			*value;
}					t_b_export;

int					init_struct_export_values(t_mns *mns, t_b_export *export_s,
	char *line);
char				**init_export_tabl(char **tabl);
t_bool				export_use_join(char *cmd);
int					get_export_values(t_b_export *export_s, char *line);
int					check_export_errors(t_b_export *export_s);
int					export_set_env(t_mns *mns, t_b_export *export_s);
int					realloc_tab_set_values(char **new_tab, int line_add,
	char **tabl);
char				**ft_realloc_tab(char **tabl, int col_add, int line_add,
	t_bool tf);

t_bool				str_has_equal(char *str);
t_bool				value_already_existing(char **envp, char *str);
int					get_envp_line(char *cmd, char **envp, char delimiteur);
int					set_envp_value(t_b_export *export_s, char ***envp);
int					b_export_display(t_mns *mns);
t_bool				export_has_multiple_join(char *line);
t_bool				export_start_good(char *line);
int					init_export_struct(t_mns *mns, t_b_export *export_s,
	char *line);
int					export_errors(char *str);
int					check_export_warnings(t_b_export *export_s);

/*
**	Utils Envp
*/

char				*get_env_var(char **envp, char *to_find, int free_to_find);
char				*get_env_name(char *str, int i);

/*
**	Builtins
*/

int					b_echo(t_mns *mns, char **tabl);

int					b_cd(t_mns *mns, char **tabl, int i_path);
int					cd_use_multiple_args(char **tabl, int i_path);
int					cd_check_specials_paths(char *path);
int					cd_start_with_path(t_mns *mns, char **tabl);
int					set_pwd(t_mns *mns);
int					check_path(t_mns *mns, char *path, char *old_path);

int					b_pwd(t_mns *mns, t_bool using_nl);
int					b_env(t_mns *mns, char **tabl);
int					b_export(t_mns *mns, char **tabl);
int					b_unset(t_mns *mns, char **tabl, char **envp);

int					b_exit(t_mns *mns, t_bool write_exit);
int					init_exit_struct(t_mns *mns, char **tabl);
int					init_exit(t_mns *mns);

/*
**	Redirections
*/

typedef struct		s_redirection
{
	char			all_redir[5][3];
	char			**cmd_tab;
	char			**redir_tab;
	char			**final_redir_tab;
	int				first_redir_pos;
	int				nb_redir;
	int				actu_redir;
	int				redir_valid;
}					t_redirection;

typedef struct		s_cpipe
{
	pid_t			pid;
	int				status;
}					t_cpipe;

typedef struct		s_pipe
{
	char			***pipe_tab;
	int				current_pipe;
	int				fd_current[2];
	int				fd_prev;
	int				nb_pipe;
	int				nb_args;
	int				pipe_valid;
	t_cpipe			*ac_pipes;
}					t_pipe;

t_bool				r_is_redirection(char *str);
int					p_pipe(t_mns *mns, char **tabl);
char				**r_get_tab_without_redirection(char **tabl);
int					r_get_redirection_pos(char **tabl);
int					main_redirections(t_mns *mns, char **tabl);
char				**r_get_tab_before_redirection(char **tabl);
char				**r_get_tab_after_redirection(char **tabl);
char				**redirection_fix_args(char **tabl);
int					r_get_redirection_type(char *str);
t_bool				r_is_pipe(char *str);
t_bool				ft_free_tab(char **tabl);

char				*append_path_tab_make_path(char **sysbin_loc, char *str,
	struct stat stat);
char				**append_path_tab(char **cmd_tab, char **envp);

char				**sort_args(char **tabl);
char				**sort_redir(char **tabl, int start);
char				**final_redir_tab(char **cmd_tab, char **redir_tab);
int					multiple_redirection_suite(char **tabl);

int					find_first_redirection_pos(char **tabl);
int					count_redir(char **tabl);
int					count_args(char **tabl);
t_bool				last_arg_is_redirection(char **tabl);

int					free_redirections(t_redirection *redir);
t_bool				redirections_error(char **tabl);
t_redirection		init_redirection_struct(char **tabl, char **envp);

int					check_signal(int state);

char				***make_pipe_tab(char **tab_exec);
int					free_pipes(t_pipe *pipe);

t_bool				pipes_valid(char **tabl);

int					init_pipe_struct(t_pipe *pipe_s, char **tab_exec);
int					first_pipe(t_mns *mns, t_pipe *pipe);
int					last_pipe(t_mns *mns, t_pipe *pipe);

/*
**	Signaux
*/

int					init_signals_handle(t_mns *mns);
void				reset_signals();
void				clear_term(char *line);

/*
** PID & State
*/

t_pid				*get_spid();

int					pid_update(pid_t pid);
pid_t				pid_getpid();

int					state_update(int state);
int					state_getstate();

/*
** Last Return
*/

int					update_last_return(t_mns *mns, int last_return);
int					get_last_return(t_mns *mns);

/*
**	BONUS FUNCTIONS
*/

int					bonus_redirection(t_mns *mns, t_redirection *redir);

char				*get_end_str(char **tabl);
char				*read_line();
int					get_tab_size(char **tabl);

void				remove_parenthesis(char *str);

#endif
