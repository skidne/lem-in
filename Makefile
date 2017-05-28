# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgore <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/23 17:00:24 by pgore             #+#    #+#              #
#    Updated: 2017/05/28 20:15:27 by pgore            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC = gcc -Wall -Wextra -Werror
INC = -I ./includes/
LBFT = libft
SRC =	src/read.c \
		src/check.c \
		src/utils.c \
		src/dijkstra.c \
		src/print_subject.c \
		src/move.c \
		src/free.c \
		src/main.c

all: $(NAME)

$(NAME):
	make -C libft
	$(CC) $(SRC) $(INC) -L$(LBFT) -lft -o $(NAME)

clean:
	make clean -C libft

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
