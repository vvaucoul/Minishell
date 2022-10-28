# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/17 10:12:54 by mle-faou          #+#    #+#              #
#    Updated: 2022/10/28 17:29:47 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRCS			=	srcs/signals/signals.c \
					srcs/main.c \
					srcs/redirections/redirections_initialisation.c \
					srcs/redirections/redirections_utils.c \
					srcs/redirections/redirections_init.c \
					srcs/redirections/redirections.c \
					srcs/redirections/redirections_make_path.c \
					srcs/redirections/redirections_utils_02.c \
					srcs/utils/utils_display_errors_2.c \
					srcs/utils/pid/mns_pid_02.c \
					srcs/utils/pid/mns_pid.c \
					srcs/utils/last_return/mns_last_return.c \
					srcs/utils/utils.c \
					srcs/utils/ft_strjoin_tf.c \
					srcs/utils/b_utils.c \
					srcs/utils/utils3.c \
					srcs/utils/free.c \
					srcs/utils/utils_debug.c \
					srcs/utils/envp.c \
					srcs/utils/start_shell.c \
					srcs/utils/utils4.c \
					srcs/utils/utils_display_errors.c \
					srcs/utils/util_display_returns.c \
					srcs/pipe/pipe_end_pipes.c \
					srcs/pipe/pipe_error.c \
					srcs/pipe/pipe_init.c \
					srcs/pipe/pipes_specials.c \
					srcs/pipe/pipe.c \
					srcs/builtins/b_exit.c \
					srcs/builtins/export/b_export_realloc_envp.c \
					srcs/builtins/export/b_export_init_values.c \
					srcs/builtins/export/b_export_errors.c \
					srcs/builtins/export/b_export_display.c \
					srcs/builtins/export/b_export.c \
					srcs/builtins/export/b_export_utils.c \
					srcs/builtins/export/b_export_init.c \
					srcs/builtins/export/b_export_set_env.c \
					srcs/builtins/b_utils.c \
					srcs/builtins/b_env.c \
					srcs/builtins/b_unset.c \
					srcs/builtins/b_echo.c \
					srcs/builtins/cd/b_cd.c \
					srcs/builtins/cd/b_cd_specials_path.c \
					srcs/builtins/cd/b_cd_utils.c \
					srcs/builtins/b_pwd.c \
					srcs/minishell/minishell.c \
					srcs/minishell/input/get_input.c \
					srcs/minishell/exec/exec_input.c \
					srcs/minishell/exec/exec_specials_cmd.c \
					srcs/minishell/exec/exec_builtins.c \
					srcs/minishell/exec/exec_pipes_redirections.c \
					srcs/minishell/exec/exec_system.c \
					srcs/minishell/parsing/update_input.c \
					srcs/minishell/parsing/update_star.c \
					srcs/minishell/parsing/quotesplit.c \
					srcs/minishell/parsing/wildcard/check_star_02.c \
					srcs/minishell/parsing/wildcard/check_star.c \
					srcs/minishell/parsing/wildcard/check_star_01.c \
					srcs/minishell/parsing/ultimate_split/ultimate_split_02.c \
					srcs/minishell/parsing/ultimate_split/ultimate_split.c \
					$(LIBS_FOLDER)libft.a

BONUS_SRCS		=	srcs/bonus/redirection_bonus/redirection_bonus.c \
					srcs/bonus/redirection_bonus/redirection_bonus_utils.c \
					srcs/bonus/minishell/minishell_bonus.c \
					srcs/bonus/operator_split/operator_split_utils_end.c \
					srcs/bonus/operator_split/operator_split.c \
					srcs/bonus/operator_split/operator_split_tab.c \
					srcs/bonus/operator_split/operator_split_assign_tab.c \
					srcs/bonus/operator_split/operator_split_utils.c \
					srcs/bonus/parenthesis/parenthesis_bonus.c \
					$(LIBS_FOLDER)mns_termcaps_lib.a

SRCS_FOLDER		=	./srcs/
LIBS_FOLDER		=	./libs/
LIBFT_FOLDER	=	./libft/
LIBFT_LIB		=	$(LIBFT_FOLDER)libft.a
TERMCAPS_FOLDER	=	./termcaps/
TERMCAPS_LIB	=	$(TERMCAPS_FOLDER)mns_termcaps_lib.a

OBJS			=	$(SRCS:.c=.o)
BONUS_OBJS		=	$(BONUS_SRCS:.c=.o)

CFLAGS			=	-lncurses -g3 -D BONUS=$(shell cat .bonus) -Wall -Wextra -Werror

HEADERS			=	./includes/
OPTION			=	$(CFLAGS) -I$(HEADERS) -I$(LIBFT_FOLDER)
OPTION_BONUS	=	$(CFLAGS) -I$(HEADERS) -I$(LIBFT_FOLDER) -I$(TERMCAPS_FOLDER)

# This is a minimal set of ANSI/VT100 color codes
_END=$'\033[0m
_BOLD=$'\033[1m
_UNDER=$'\033[4m
_REV=$'\033[7m

# Colors
_GREY=$'\033[1;30m
_RED=$'\033[1;31m
_GREEN=$'\033[1;32m
_YELLOW=$'\033[1;33m
_BLUE=$'\033[1;34m
_PURPLE=$'\033[1;35m
_CYAN=$'\033[1;36m
_WHITE=$'\033[1;37m

# Inverted, i.e. colored backgrounds
_IGREY=$'\033[1;40m
_IRED=$'\033[1;41m
_IGREEN=$'\033[1;42m
_IYELLOW=$'\033[1;43m
_IBLUE=$'\033[1;44m
_IPURPLE=$'\033[1;45m
_ICYAN=$'\033[1;46m
_IWHITE=$'\033[1;47m

all:
	@printf "0" > .bonus
	@printf "\n\n\n$(_BOLD)$(_GREEN)        :::   :::   ::::    :::  :::::::: \n"
	@printf "      :+:+: :+:+:  :+:+:   :+: :+:    :+: \n"
	@printf "    +:+ +:+:+ +:+ :+:+:+  +:+ +:+         \n"
	@printf "   +#+  +:+  +#+ +#+ +:+ +#+ +#++:++#++   \n"
	@printf "  +#+       +#+ +#+  +#+#+#        +#+    \n"
	@printf " #+#       #+# #+#   #+#+# #+#    #+#     \n"
	@printf "###       ### ###    ####  ########       $(_END)\n\n\n\n"
	@printf "$(_PURPLE)Creating \"libs\" directory . . . $(_END)\n"
	@mkdir -p libs
	@cd libft && make -s
	@printf "$(_PURPLE)Copying libft into \"libs\" directory . . . $(_END)\n"
	@cp $(LIBFT_LIB) $(LIBS_FOLDER)
	@make -s $(NAME)

%.o : %.c
	@gcc $(OPTION) -I. -c $< -o ${<:.c=.o}

$(NAME):
	@printf "$(_PURPLE)Keeping code under control . . . $(_END)\n"
	@printf "$(_PURPLE)Creating pre-compilation files for minishell . . . $(_END)\n"
	@make $(OBJS)
	@/bin/rm .bonus
	@printf "$(_PURPLE)Compiling minishell . . . $(_END)\n"
	@gcc $(OPTION) -o $(NAME) $(OBJS)
	@printf "$(_BOLD)$(_GREEN)   ___                  __\n"
	@printf "  / _ \___  ___  ___   / /\n"
	@printf " / // / _ \/ _ \/ -_) /_/\n"
	@printf "/____/\___/_//_/\__/ (_)$(_END)\n"

clean:
	@cd libft && make -s fclean
	@cd termcaps && make -s fclean
	@printf "$(_PURPLE)Deleting \"libs\" content . . . $(_END)\n"
	@printf "$(_PURPLE)Deleting \"libs\" directory . . . $(_END)\n"
	@/bin/rm -rf $(LIBS_FOLDER)
	@printf "$(_PURPLE)Deleting pre-compilation files for minishell . . . $(_END)\n"
	@/bin/rm -f $(OBJS)
	@/bin/rm -f $(BONUS_OBJS)

fclean: clean
	@printf "$(_PURPLE)Deleting executable for minishell . . . $(_END)\n"
	@/bin/rm -f $(NAME)

re: fclean all

bonus:
	@printf "$(_BOLD)$(_GREEN)        :::   :::   ::::    :::  :::::::: \n"
	@printf "      :+:+: :+:+:  :+:+:   :+: :+:    :+: \n"
	@printf "    +:+ +:+:+ +:+ :+:+:+  +:+ +:+         \n"
	@printf "   +#+  +:+  +#+ +#+ +:+ +#+ +#++:++#++   \n"
	@printf "  +#+       +#+ +#+  +#+#+#        +#+    \n"
	@printf " #+#       #+# #+#   #+#+# #+#    #+#     \n"
	@printf "###       ### ###    ####  ########       $(_END)\n"
	@printf "$(_BOLD)$(_YELLOW)                                         __   ____                        \n"
	@printf "                        ____ _____  ____/ /  / __ )____  ____  __  _______\n"
	@printf "                       / __ \`/ __ \/ __  /  / __  / __ \/ __ \/ / / / ___/\n"
	@printf "                      / /_/ / / / / /_/ /  / /_/ / /_/ / / / / /_/ (__  ) \n"
	@printf "                      \__,_/_/ /_/\__,_/  /_____/\____/_/ /_/\__,_/____/  $(_END)\n"
	@printf "$(_PURPLE)Cleaning . . . $(_END)\n"
	@make -s fclean
	@printf "$(_PURPLE)Creating \"libs\" directory . . . $(_END)\n"
	@mkdir -p libs
	@cd libft && make -s
	@printf "$(_PURPLE)Copying libft into \"libs\" directory . . . $(_END)\n"
	@cp $(LIBFT_LIB) $(LIBS_FOLDER)
	@cd termcaps && make -s
	@printf "$(_PURPLE)Copying termcaps_lib into \"libs\" directory . . . $(_END)\n"
	@cp $(TERMCAPS_LIB) $(LIBS_FOLDER)
	@printf "$(_PURPLE)Activating $(_YELLOW)bonus$(_PURPLE) for minishell . . . $(_END)\n"
	@printf "1" > .bonu\ns
	@printf "$(_PURPLE)Creating pre-compilation files for minishell . . . $(_END)\n"
	@make -s $(OBJS)
	@printf "$(_CYAN)\tDone !$(_END)\n"
	@printf "$(_PURPLE)Creating pre-compilation $(_YELLOW)bonus$(_PURPLE) files for minishell . . . $(_END)\n"
	@make -s $(BONUS_OBJS)
	@/bin/rm .bonus
	@printf "$(_CYAN)\tDone !$(_END)\n"
	@printf "$(_PURPLE)Compiling minishell with $(_YELLOW)bonus$(_PURPLE). . . $(_END)\n"
	@gcc $(OBJS) $(BONUS_OBJS) $(OPTION_BONUS) -o $(NAME)
	@printf "$(_BOLD)$(_YELLOW)   ___                  __\n"
	@printf "  / _ \___  ___  ___   / /\n"
	@printf " / // / _ \/ _ \/ -_) /_/\n"
	@printf "/____/\___/_//_/\__/ (_)$(_END)\n"

.PHONY: all clean fclean re
