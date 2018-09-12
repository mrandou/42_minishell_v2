# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/15 13:40:23 by mrandou           #+#    #+#              #
#    Updated: 2018/09/12 17:46:15 by mrandou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=		minishell

CC			=		gcc

CFLAGS		=		-Wall -Wextra -Werror

#######
# INC #
#######

INC_DIR		=		incs/

INC_NAME	=\
	minishell.h\

INC			=		$(addprefix $(INC_DIR), $(INC_NAME))

INC_DIR_ALL	=\
	$(INC_DIR)\

ICFLAGS		=		$(addprefix -I, $(INC_DIR_ALL))


#######
# SRC #
#######

SRC_DIR		=		srcs/

SRC_NAME	=\
	minishell.c sh_style.c sh_builtin.c sh_split.c sh_parse.c sh_env.c\
	sh_bin.c sh_env_builtin.c sh_expand.c sh_cd_builtin.c

SRC			=		$(addprefix $(SRC_DIR), $(SRC_NAME))

#######
# OBJ #
#######

OBJ_DIR		=		obj/

OBJ_NAME	=		$(SRC_NAME:.c=.o)

OBJ			=		$(addprefix $(OBJ_DIR), $(OBJ_NAME))

#######
# LIB #
#######

LDFLAGS		=		-Llibft

LIBFT_DIR = libft/

LDLIBS		=		-lft
LDIBS_DIR = $(LIBFT_DIR)incs
LIBFT = $(LIBFT_DIR)libft.a

SRC_LIBFT_NAME = $(shell make -C $(LIBFT_DIR) print-SRC)

SRC_LIBFT = $(addprefix $(LIBFT_DIR), $(SRC_LIBFT_NAME))
ICFLAGS		+=		$(addprefix -I, $(LDIBS_DIR))


########
# RULE #
########

all: 				$(NAME)

$(NAME):		$(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $@ $(LIBFT) -g3

$(LIBFT): $(SRC_LIBFT)
	make -C libft

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)%.o:		 $(SRC_DIR)%.c ./Makefile $(INC)
	$(CC) $(CFLAGS) $(ICFLAGS) -c $< -o $@

clean:
	make -C libft clean
	$(RM) $(OBJ)

fclean:
	rm -rf $(OBJ_DIR)
	make -C . clean

re: fclean all

print-%:
	@echo $($*)
