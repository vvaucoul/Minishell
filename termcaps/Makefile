# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/26 18:34:22 by vvaucoul          #+#    #+#              #
#    Updated: 2020/11/04 10:47:48 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	mns_termcaps_lib.a

SRCS			=	srcs/read/read_line.c \
					srcs/read/get_key.c \
					srcs/read/cmp_line_keys.c \
					srcs/line_edition/line.c \
					srcs/line_edition/line_utils.c \
					srcs/utils/get_next_line.c \
					srcs/utils/utils.c \
					srcs/utils/utils_02.c \
					srcs/utils/ft_memcmp.c \
					srcs/cursor_motion/cursor.c \
					srcs/cursor_motion/shift_words_dw.c \
					srcs/cursor_motion/shift_words.c \
					srcs/copy_paste/copy_paste_utils.c \
					srcs/copy_paste/copy_past.c \
					srcs/history/history.c \
					srcs/history/history_utils.c \
					srcs/multilines_edition/multi_line_edition.c \
					srcs/multilines_edition/multi_line_utils.c \
					srcs/termios.c \
					$(LIBFT)

OBJS			=	$(SRCS:.c=.o)
BONUS_OBJS		=	$(BONUS_SRCS:.c=.o)
CFLAGS			=	-lncurses -g3 -Wall -Wextra -Werror
LIBFT_PATH		=	../libft/
LIBFT			=	libft.a
LIBS_OPTIONS	= 	libft.a mns_termcaps_lib.a
OPTION			=	$(CFLAGS) -I$(LIBFT_PATH) -I.

# This is a minimal set of ANSI/VT100 color codes
_END=$'\033[0m
_BOLD=$'\033[1;1m
_UNDER=$'\033[1;4m
_REV=$'\033[1;7m

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
	@echo "$(_PURPLE)Copying libft into termcaps. . . $(_END)"
	@cp $(LIBFT_PATH)$(LIBFT) .
	@make $(NAME)
	@echo "$(_CYAN)\tDone !$(_END)"

%.o : %.c
	@gcc $(OPTION) -c $< -o ${<:.c=.o}

$(NAME):
	@echo "$(_PURPLE)Creating pre-compilation files for termcaps . . . $(_END)"
	@make $(OBJS)
	@echo "$(_CYAN)\tDone !$(_END)"
	@echo "$(_PURPLE)Compiling mns_termcaps_lib . . . $(_END)"
	@ar rcs $(NAME) $(OBJS)

test:
# 	@make $(HEADERS)
	@echo "$(_PURPLE)Creating test for termcaps lib. . . $(_END)"
	@make
	@gcc srcs/main.c -I. $(LIBS_OPTIONS) -I../libft ../libft/libft.a $(OPTION) -o termcaps_test

clean:
	@echo "$(_PURPLE)Deleting pre-compilation files for termcaps . . . $(_END)"
	@/bin/rm -f $(OBJS)
	@echo "$(_PURPLE)Deleting libft copy . . . $(_END)"
	@/bin/rm -f libft.a

fclean: clean
	@echo "$(_PURPLE)Deleting executable for termcaps . . . $(_END)"
	@/bin/rm -f $(NAME)
	@/bin/rm -f termcaps_test

re: fclean all

.PHONY: all clean fclean re
