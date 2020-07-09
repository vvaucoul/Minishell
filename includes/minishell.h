#ifndef MINISHELL_H
#define MINISHELL_H

//malloc, free, exit
#include <stdlib.h>
//write, read, close, fork, getcwd, chdir, stat, lstat, fstat, execve, dup, dup2, pipe
#include <unistd.h>
//open, wait, waitpid, kill, stat, lstat, fstat, opendir, closedir
#include <sys/types.h>
//open, stat, lstat, fstat
#include <sys/stat.h>
//open
#include <fcntl.h>
//wait, waitpid, wait3, wait4
#include <sys/wait.h>
//wait3, wait4
#include <sys/time.h>
//wait3, wait4
#include <sys/resource.h>
//wait3, wait4
#include <sys/wait.h>
//signal, kill
#include <signal.h>
//opendir, readdir, closedir
#include <dirent.h>
//strerror
#include <string.h>
//errno
#include <errno.h>


//bonus
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

typedef int T_BOOL;
#define TRUE 1
#define FALSE 0

#define MAX_CHAR_IN_PROMPT 4096 //todo rm
#define ENV_DELIMITEUR '=' //todo rm

#include "../libft/libft.h"

#include <stdio.h> //todo rm

typedef struct	s_mns
{
	char		**envp;
	int			last_return;
}				t_mns;

//main.c
// int			main(int argc, char const *argv[], char **envp);
char			*check_homedollar(char **str, t_mns *mns);

// get_input.c
int				get_input(char **input, t_mns *mns);

//util1.c
void			exit_shell(void);
int				init_mns(t_mns *mns, char **envp, int argc, char const *argv[]);
int				is_in_quotes(char *str, int pos);
char			*get_cmd_in_path(char *path);
char			**remove_builtin_in_tab(char **tab);
T_BOOL			b_isvalid(char *str);

//exec_builtins.c
int				exec_builtins(char **command, t_mns *mns);

//envp.c
char			*get_env_var(char **envp, char *to_find, int free_to_find);
char			*get_env_name(char *str, int i);
char			*get_env_value(char *value, char **envp);

//exec_exe.c
int				exec_system(char **command, t_mns *mns);

// quotesplit.c
char			**quotesplit(char *str, char c);

//bonus
//termcaps_bonus.c
// int				init_termcaps(t_mns *mns);

/// vv
int				b_echo(char **tab, T_BOOL has_argument);
int				b_cd(t_mns *mns, char *path);
int				b_pwd(char **envp, T_BOOL using_nl);
int				b_exit();
int				b_env(t_mns *mns);
int				b_export(t_mns *mns, char **tab);
int				b_unset(char **tab, char **envp);
int				run(t_mns *mns, char *path, char **args, char **envp);
int				*parse_arguments(char **args);
T_BOOL			r_is_redirection(char *str);
int				main_redirections(char *cmd, char **tab, char **envp);
int				p_pipe(char **tab, char **envp);
int				exec(char **tab, char **envp);
char			**r_get_tab_without_redirection(char **tab);
int				r_get_redirection_pos(char **tab);


// int				minishell(t_mns *mns);
// int				*parse_arguments(char **args);

// T_BOOL			b_isvalid(char *str);



// int				init_signals_handle();

// char			**r_get_tab_without_pipe(char **tab);


#endif
