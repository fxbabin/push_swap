# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbabin <fbabin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/05 22:43:45 by fbabin            #+#    #+#              #
#    Updated: 2018/01/16 14:33:51 by fbabin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CHECKER			= checker
PUSH_SWAP		= push_swap

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -g3 -fsanitize=address

_SRCS			=	checks.c display.c operations.c utils.c utils_2.c gets.c \
					small_sort.c min_costcalc.c opti_sort.c optimize.c \

_PS_SRCS		=	push_swap.c
_PS_SRCS		+=	$(_SRCS)
_C_SRCS			=	checker.c 
_C_SRCS			+=	$(_SRCS)
_LIBFT			=	libft.a

SRCS_DIR		= srcs
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
		@$(CC) $(CFLAGS) -o $(CHECKER) $(C_OBJS) -L$(LIB_DIR) -lft -I includes
		@echo "$(CHECKER) : $(_GREEN)Done$(_END)"

$(PUSH_SWAP): $(LIBFT) $(PS_OBJS)
		@$(CC) $(CFLAGS) -o $(PUSH_SWAP) $(PS_OBJS) -L$(LIB_DIR) -lft -I includes
		@echo "$(PUSH_SWAP) : $(_GREEN)Done$(_END)"

$(LIBFT):
		@make -C $(LIB_DIR)

%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $@ -I includes

clean:
		@make fclean -C $(LIB_DIR)
		@/bin/rm -f $(C_OBJS) $(PS_OBJS)
		@echo "push_swap clean : $(_GREEN)Done$(_END)"

fclean: clean
		@/bin/rm -f $(CHECKER) $(PUSH_SWAP)
		@echo "push_swap fclean : $(_GREEN)Done$(_END)"

re:
		@make fclean
		@make

.PHONY: all clean fclean re
