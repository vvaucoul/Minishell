# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/25 18:04:06 by vvaucoul          #+#    #+#              #
#    Updated: 2020/07/01 18:11:00 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


### COMPILATION ###
CC				= gcc
CFLAGS			= -I $(HEADER) -I $(LIB_DIR) -I$(LIB_UP_DIR)
LIBS			= -g3 #-Wall -Wextra -Werror

### EXECUTABLE ###
NAME			= minishell

### INCLUDES ###
HEADER 			= ./includes/
LIBFT  			= libft.a
LIBFT_UP  		= libft_upgraded.a
LIB_DIR			= ./libft/
LIB_UP_DIR		= ./libft/libft_upgraded/
ALL_LIB_DIR		= ./libraries/
OBJ_PATH 		= obj
SRC_PATH 		= src


### SOURCES ###
SRCS			=	$(wildcard srcs/*.c)			\
					$(wildcard srcs/builtins/*.c)	\
					$(wildcard srcs/env/*.c)		\
					$(wildcard srcs/signals/*.c)	\
					$(wildcard srcs/redirections/*.c)	\
					$(wildcard srcs/utils/*.c)	\

### OBJECTS ###
OBJS			=         $(SRCS:.c=.o)

%.o : %.c
	@$(CC) $(FLAGS) -I. -c $< -o ${<:.c=.o}

### COLORS ###
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

### CLEAN ###
RM				= rm -f

### RULES ###

all:			obj_dir comp_libs $(NAME)

comp_libs:
				@echo "\t$(WHITE)[] $(YELLOW) COMPILATION - LIBFT -$(NOC)"
				@make -C $(LIB_DIR)
				@echo "\t$(WHITE)[] $(VIOLET) Copie de la librairie dans le dossier root$(NOC)"
				@cp $(LIB_DIR)$(LIBFT) $(ALL_LIB_DIR)
				@echo "\t$(WHITE)[] $(YELLOW) COMPILATION - LIBFT UPGRADED -$(NOC)"
				@make -C $(LIB_UP_DIR)
				@echo "\t$(WHITE)[] $(VIOLET) Copie de la librairie dans le dossier root$(NOC)\n"
				@cp $(LIB_UP_DIR)$(LIBFT_UP) $(ALL_LIB_DIR)

$(NAME):
				@echo "\t$(WHITE)[] $(YELLOW) COMPILATION en cours$(NOC)\n"
				@$(CC) $(SRCS) $(CFLAGS) -L $(ALL_LIB_DIR) -lft -lft_upgraded $(LIBS) -o $(NAME)
				@echo "\t$(WHITE)[] $(GREEN) MINISHELL compilé$(NOC)"

obj_dir:
				@echo "\t$(WHITE)[] $(CYAN) Create obj folder$(NOC)"
				@mkdir -p $(OBJ_PATH)
				@echo "\t$(WHITE)[] $(CYAN) Create libraries folder$(NOC)\n"
				@mkdir -p $(ALL_LIB_DIR)

clean:
				@echo "\t$(WHITE)[] $(RED) Supression des .o$(NOC)"
				@$(RM) $(OBJS)
				@echo "\t$(WHITE)[] $(RED) Supression des librairies .a$(NOC)"
				@cd $(LIB_DIR) && $(MAKE) fclean
				@cd $(LIB_UP_DIR) && $(MAKE) fclean
				@$(RM) -r $(ALL_LIB_DIR)
				@$(RM) -r $(OBJ_PATH)

fclean:			clean
				@echo "\t$(WHITE)[] $(RED) fichier binaires supprimés$(NOC)\n"
				@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
