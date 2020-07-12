# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/17 10:12:54 by mle-faou          #+#    #+#              #
#    Updated: 2020/07/12 16:52:08 by vvaucoul         ###   ########.fr        #
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
					libft/libft.a

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
OBJS			=	$(SRCS:.c=.o)
BONUS_OBJS		=	$(BONUS_SRCS:.c=.o)
CFLAGS			=	-g3 #m-Wall -Wextra -Werror
HEADERS			=	./includes/
OPTION			=	$(CFLAGS) -I$(HEADERS) -I./libft

%.o : %.c
	@gcc $(OPTION) -I. -c $< -o ${<:.c=.o}

all:
	cd libft && make
	# mkdir libs
	# cp ./libft/libft.a ./libs
	make $(NAME)

$(NAME): $(OBJS)
	@gcc $(OPTION) -o $(NAME) $(OBJS)

clean:
	@/bin/rm -f $(OBJS)
	cd libft && make fclean

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

bonus:$(BONUS_OBJS)
	@gcc $(OPTION) -o $(NAME) $(BONUS_OBJS)

.PHONY: all clean fclean re
