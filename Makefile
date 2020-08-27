# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/17 10:12:54 by mle-faou          #+#    #+#              #
#    Updated: 2020/08/26 18:44:28 by mle-faou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME			=	minishell

SRCS			=	$(wildcard srcs/*.c)			\
					$(wildcard srcs/builtins/*.c)	\
					$(wildcard srcs/signals/*.c)	\
					$(wildcard srcs/redirections/*.c)	\
					$(wildcard srcs/minishell/*.c)	\
					$(wildcard srcs/utils/*.c)	\
					$(wildcard srcs/minishell/parsing/*.c)	\
					$(wildcard srcs/minishell/input/*.c)	\
					$(wildcard srcs/minishell/exec/*.c)	\
					$(wildcard srcs/bonus/*.c)	\
					$(wildcard srcs/bonus/termcaps/*.c)	\
					$(LIB_FOLDER)libft.a	\
					$(LIB_FOLDER)mns_termcaps_lib.a
					# libft/libft.a \
					# $(SRCS_FOLDER)main.c \
					# $(SRCS_FOLDER)envp.c \
					# $(SRCS_FOLDER)exec_builtins.c \
					# $(SRCS_FOLDER)exec_system.c \
					# $(SRCS_FOLDER)util1.c \
					# $(SRCS_FOLDER)quotesplit.c \
					# $(SRCS_FOLDER)get_input.c \
					# $(SRCS_FOLDER)parse_arguments.c \
					# $(SRCS_FOLDER)run.c \
					# $(SRCS_FOLDER)/builtins/b_echo.c \
					# $(SRCS_FOLDER)/builtins/b_cd.c \
					# $(SRCS_FOLDER)/builtins/b_pwd.c \
					# $(SRCS_FOLDER)/builtins/b_export.c \
					# $(SRCS_FOLDER)/builtins/b_unset.c \
					# $(SRCS_FOLDER)/builtins/b_env.c \
					# $(SRCS_FOLDER)/builtins/b_exit.c \
					# $(SRCS_FOLDER)/redirections/redirections.c \
					# $(SRCS_FOLDER)/redirections/redirections_utils.c \
					# $(SRCS_FOLDER)/redirections/pipe.c \
# BONUS_SRCS		=	$(SRCS_FOLDER)main.c \
# 					$(SRCS_FOLDER)envp.c \
# 					$(SRCS_FOLDER)exec_builtins.c \
# 					$(SRCS_FOLDER)exec_system.c \
# 					$(SRCS_FOLDER)util1.c \
# 					$(SRCS_FOLDER)quotesplit.c \
# 					libft/libft.a
					# $(SRCS_FOLDER)termcaps_bonus.c \
					# $(SRCS_FOLDER)get_input_bonus.c \

SRCS_FOLDER		=	srcs/
TERMCAPS_LIB	=	termcaps/mns_termcaps_lib.a
TERMCAPS_HEADER	=	./termcaps/termcaps_bonus.h
LIBFT			=	libft/libft.a
LIB_FOLDER		=	libs/

OBJS			=	$(SRCS:.c=.o)
BONUS_OBJS		=	$(BONUS_SRCS:.c=.o)
CFLAGS			=	-g3 -Wall -Wextra -Werror -D BONUS=0
HEADERS			=	./includes/
OPTION			=	$(CFLAGS) -I$(HEADERS) -I./libft -I$(TERMCAPS_HEADER)

# This is a minimal set of ANSI/VT100 color codes
_END=$'\033[0m
_BOLD=$'\033[1m
_UNDER=$'\033[4m
_REV=$'\033[7m

# Colors
_GREY=$'\033[30m
_RED=$'\033[31m
_GREEN=$'\033[32m
_YELLOW=$'\033[33m
_BLUE=$'\033[34m
_PURPLE=$'\033[35m
_CYAN=$'\033[36m
_WHITE=$'\033[37m

# Inverted, i.e. colored backgrounds
_IGREY=$'\033[40m
_IRED=$'\033[41m
_IGREEN=$'\033[42m
_IYELLOW=$'\033[43m
_IBLUE=$'\033[44m
_IPURPLE=$'\033[45m
_ICYAN=$'\033[46m
_IWHITE=$'\033[47m

all:
	@echo "$(_BOLD)$(_GREEN)        :::   :::   ::::    :::  :::::::: "
	@echo "      :+:+: :+:+:  :+:+:   :+: :+:    :+: "
	@echo "    +:+ +:+:+ +:+ :+:+:+  +:+ +:+         "
	@echo "   +#+  +:+  +#+ +#+ +:+ +#+ +#++:++#++   "
	@echo "  +#+       +#+ +#+  +#+#+#        +#+    "
	@echo " #+#       #+# #+#   #+#+# #+#    #+#     "
	@echo "###       ### ###    ####  ########       $(_END)"
	@echo "$(_PURPLE)Creating \"libs\" directory . . . $(_END)"
	@mkdir -p libs
	@cd libft && make
	@echo "$(_PURPLE)Copying libft into \"libs\" directory . . . $(_END)"
	@cp $(LIBFT) $(LIB_FOLDER)
	@cd termcaps && make
	@echo "$(_PURPLE)Copying termcaps_lib into \"libs\" directory . . . $(_END)"
	@cp $(TERMCAPS_LIB) $(LIB_FOLDER)
	@make $(NAME)

%.o : %.c
	@gcc $(OPTION) -I. -c $< -o ${<:.c=.o}

$(NAME):
	@echo "$(_PURPLE)Creating pre-compilation files for minishell . . . $(_END)"
	@make $(OBJS)
	@echo "$(_CYAN)\tDone !$(_END)"
	@echo "$(_PURPLE)Compiling minishell . . . $(_END)"
	@gcc $(OPTION) -lncurses -ltermcap -o $(NAME) $(OBJS)
		@echo "$(_BOLD)$(_GREEN)   ___                  __"
	@echo "  / _ \___  ___  ___   / /"
	@echo " / // / _ \/ _ \/ -_) /_/"
	@echo "/____/\___/_//_/\__/ (_)$(_END)"


clean:
	@echo "$(_BOLD)$(_GREEN)                ||"
	@echo "                ||"
	@echo "                ||"
	@echo "                ||"
	@echo "                ||"
	@echo "                ||"
	@echo "                ||     Here you go, sweep"
	@echo "                ||     that up..........."
	@echo "               /||\\"
	@echo "              /||||\\"
	@echo "              ======         __|__"
	@echo "              ||||||        / ~@~ \\"
	@echo "              ||||||       |-------|"
	@echo "              ||||||       |_______|$(_END)"
	@echo "$(_PURPLE)Deleting pre-compilation files for minishell . . . $(_END)"
	@/bin/rm -f $(OBJS)
	@cd libft && make fclean
	@cd termcaps && make fclean

fclean: clean
	@echo "$(_PURPLE)Deleting \"libs\" content . . . $(_END)"
	@echo "$(_PURPLE)Deleting \"libs\" directory . . . $(_END)"
	@/bin/rm -rf $(LIB_FOLDER)
	@echo "$(_PURPLE)Deleting executable for minishell . . . $(_END)"
	@/bin/rm -f $(NAME)

re: fclean all

bonus:
	@echo "$(_BOLD)$(_GREEN)        :::   :::   ::::    :::  :::::::: "
	@echo "      :+:+: :+:+:  :+:+:   :+: :+:    :+: "
	@echo "    +:+ +:+:+ +:+ :+:+:+  +:+ +:+         "
	@echo "   +#+  +:+  +#+ +#+ +:+ +#+ +#++:++#++   "
	@echo "  +#+       +#+ +#+  +#+#+#        +#+    "
	@echo " #+#       #+# #+#   #+#+# #+#    #+#     "
	@echo "###       ### ###    ####  ########       $(_END)"
	@echo "$(_YELLOW)                                         __   ____                        "
	@echo "                        ____ _____  ____/ /  / __ )____  ____  __  _______"
	@echo "                       / __ \`/ __ \/ __  /  / __  / __ \/ __ \/ / / / ___/"
	@echo "                      / /_/ / / / / /_/ /  / /_/ / /_/ / / / / /_/ (__  ) "
	@echo "                      \__,_/_/ /_/\__,_/  /_____/\____/_/ /_/\__,_/____/  $(_END)"
	@echo "$(_PURPLE)Creating pre-compilation $(_YELLOW)bonus$(_PURPLE) files for minishell . . . $(_END)"
	$(BONUS_OBJS)
	@echo "$(_CYAN)\tDone !$(_END)"
	@echo "$(_PURPLE)Compiling minishell with $(_YELLOW)bonus$(_PURPLE). . . $(_END)"
	@gcc $(OPTION) -o $(NAME) $(BONUS_OBJS)
	@echo "$(_BOLD)$(_GREEN)   ___                  __"
	@echo "  / _ \___  ___  ___   / /"
	@echo " / // / _ \/ _ \/ -_) /_/"
	@echo "/____/\___/_//_/\__/ (_)$(_END)"

.PHONY: all clean fclean re
