# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/26 18:34:22 by vvaucoul          #+#    #+#              #
#    Updated: 2020/08/26 17:56:26 by mle-faou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	mns_termcaps_lib.a

SRCS			=	$(wildcard srcs/copy_paste/*.c)	\
					$(wildcard srcs/cursor_motion/*.c)	\
					$(wildcard srcs/history/*.c)	\
					$(wildcard srcs/line_edition/*.c)	\
					$(wildcard srcs/multilines_edition/*.c)	\
					$(wildcard srcs/utils/*.c)	\
					$(wildcard srcs/*.c)	\
					$(wildcard srcs/read/*.c)	\

OBJS			=	$(SRCS:.c=.o)
BONUS_OBJS		=	$(BONUS_SRCS:.c=.o)
CFLAGS			=	-g3 -Wall -Wextra -Werror
HEADERS			=	../libft/
OPTION			=	$(CFLAGS) -I$(HEADERS) -I.

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
	@echo "$(_PURPLE)Copying libft into termcaps. . . $(_END)"
	@cp ../libs/libft.a .
	@make $(NAME)

%.o : %.c
	@gcc $(OPTION) -I. -c $< -o ${<:.c=.o}

$(NAME):
	@echo "$(_PURPLE)Creating pre-compilation files for termcaps . . . $(_END)"
	@make $(OBJS)
	@echo "$(_CYAN)\tDone !$(_END)"
	@echo "$(_PURPLE)Compiling mns_termcaps_lib . . . $(_END)"
	@ar rcs $(NAME) $(OBJS)

clean:
	@echo "$(_PURPLE)Deleting pre-compilation files for termcaps . . . $(_END)"
	@/bin/rm -f $(OBJS)
	@/bin/rm -f libft.a


fclean: clean
	@echo "$(_PURPLE)Deleting executable for termcaps . . . $(_END)"
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

	# @gcc $(OPTION) -L. -lft -ltermcap -o $(NAME) $(OBJS)
