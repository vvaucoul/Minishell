# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/26 18:34:22 by vvaucoul          #+#    #+#              #
#    Updated: 2020/08/21 15:54:28 by mle-faou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	termcaps
LIB_NAME		=	mns_termcaps_lib.a

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

%.o : %.c
	@gcc $(OPTION) -I. -c $< -o ${<:.c=.o}

all:
	@cp ../libs/libft.a .
	@make $(NAME)

$(NAME): $(OBJS)
	@gcc $(OPTION) -L. -lft -ltermcap -o $(NAME) $(OBJS)

lib: re
	@echo - TERMCAPS LIB -
	@ar rc $(LIB_NAME) $(OBJS)
	@ranlib $(LIB_NAME)
	@echo TERMCAPS LIB COMPLETE


clean:
	@/bin/rm -f $(OBJS)
	@/bin/rm -f $(NAME)
	@cd ../libft && make fclean

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

fclean_lib: clean
	@/bin/rm -f $(LIB_NAME)
	@/bin/rm -f libft.a

.PHONY: all clean fclean re
