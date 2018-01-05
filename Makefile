# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/05 22:43:45 by fbabin            #+#    #+#              #
#    Updated: 2018/01/05 23:31:56 by fbabin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CHECKER			= checker
PUSH_SWAP		= push_swap

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra

_SRCS			=	checks.c display.c operations.c utils.c \

_PS_SRCS		=	push_swap.c
_PS_SRCS		+=	$(_SRCS)
_C_SRCS			=	checker.c 
_C_SRCS			+=	$(_SRCS)
_LIBFT			=	libft.a

SRCS_DIR		= .
LIB_DIR			= libft
PS_SRCS			= $(addprefix $(SRCS_DIR)/, $(_PS_SRCS))
C_SRCS			= $(addprefix $(SRCS_DIR)/, $(_C_SRCS))
LIBFT			= $(addprefix $(LIB_DIR)/, $(_LIBFT))
PS_OBJS			= $(PS_SRCS:.c=.o)
C_OBJS			= $(C_SRCS:.c=.o)

#COLORS
_CYAN=\x1b[36m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_END=\x1b[0m

all: $(CHECKER) $(PUSH_SWAP)

$(CHECKER): $(LIBFT) $(C_OBJS)
		@$(CC) -o $(CHECKER) $(C_OBJS) -L$(LIB_DIR) -lft
		@echo "$(CHECKER) : $(_GREEN)Done$(_END)"

$(PUSH_SWAP): $(LIBFT) $(PS_OBJS)
		@$(CC) -o $(PUSH_SWAP) $(PS_OBJS) -L$(LIB_DIR) -lft
		@echo "$(PUSH_SWAP) : $(_GREEN)Done$(_END)"

$(LIBFT):
		@make -C $(LIB_DIR)

%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $@

clean:
		@make fclean -C $(LIB_DIR)
		@/bin/rm -f $(C_OBJS) $(PS_OBJS)
		@echo "clean : $(_GREEN)Done$(_END)"

fclean: clean
		@/bin/rm -f $(CHECKER) $(PUSH_SWAP)
		@echo "fclean : $(_GREEN)Done$(_END)"

re:
		@make fclean
		@make

.PHONY: all clean fclean re
