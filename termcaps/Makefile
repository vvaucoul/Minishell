# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/26 18:34:22 by vvaucoul          #+#    #+#              #
#    Updated: 2020/07/27 17:28:17 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	termcaps
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
CFLAGS			=	-g3 #-Wall -Wextra -Werror
HEADERS			=	../../libft/
OPTION			=	$(CFLAGS) -I$(HEADERS) -I.
%.o : %.c
	@gcc $(OPTION) -I. -c $< -o ${<:.c=.o}
all:
	cd ../libft && make
	#mkdir libs
	cp ../libft/libft.a .
	make $(NAME)
$(NAME): $(OBJS)
	@gcc $(OPTION) -L. -lft -ltermcap -o $(NAME) $(OBJS)
clean:
	@/bin/rm -f $(OBJS)
	cd ../libft && make fclean
fclean: clean
	@/bin/rm -f $(NAME)
re: fclean all
bonus:$(BONUS_OBJS)
	@gcc $(OPTION) -o $(NAME) $(BONUS_OBJS)
.PHONY: all clean fclean re
