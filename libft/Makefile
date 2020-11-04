# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/17 10:12:54 by mle-faou          #+#    #+#              #
#    Updated: 2020/11/03 17:11:37 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a
SRCS			=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
					ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c \
					ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
					ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c \
					ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c \
					ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
					ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
					ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c \
					ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c \
					ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
					ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
					ft_lstiter.c ft_lstmap.c ft_memalloc.c ft_realloc.c \
					ft_strnew.c ft_strisempty.c ft_freetab.c ft_strcmp.c \
					ft_strequ.c ft_putstr.c ft_strstartswith.c ft_strcut.c \
					ft_straddchar.c ft_isupper.c ft_islower.c ft_straddstr.c \
					ft_strcat.c ft_strtrunc_del.c ft_strchangelen.c \
					ft_tablen.c  ft_lstadd_here.c ft_freetab_onsize.c \
					ft_strrange.c ft_get_next_line.c ft_freetab_ret.c

OBJ				=	$(SRCS:.c=.o)
CFLAGS			=	-Wall -Wextra -Werror
HEADERS			=	./

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

all: $(NAME)

%.o : %.c
	@gcc $(CFLAGS) -I. -c $< -o ${<:.c=.o}

$(NAME):
	@echo "$(_PURPLE)Creating pre-compilation files for libft . . . $(_END)"
	@make $(OBJ)
	@echo "$(_CYAN)\tDone !$(_END)"
	@echo "$(_PURPLE)Compiling libft . . . $(_END)"
	@ar rcs $(NAME) $(OBJ)

clean:
	@echo "$(_PURPLE)Deleting pre-compilation files for libft . . . $(_END)"
	@/bin/rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	@echo "$(_PURPLE)Deleting executable for libft . . . $(_END)"
	@/bin/rm -f $(NAME) $(NAME:.a=.so)

re: fclean all

.PHONY: all clean fclean re
