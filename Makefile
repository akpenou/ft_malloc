# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akpenou <akpenou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/20 17:56:36 by akpenou           #+#    #+#              #
#    Updated: 2017/03/21 17:23:06 by akpenou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

SRC = src/ft_free.c src/ft_malloc.c src/ft_print.c src/ft_realloc.c src/ft_safe.c src/ft_show_mem_alloc.c src/ft_showmem.c src/ft_debug.c

OBJ = $(SRC:.c=.o)

NAME = malloc

CFLAGS = -Wall -Wextra -Werror

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	echo "\033[1;32m COMPILATION MALLOC\033[0m"
	gcc $(CFLAGS) $(OBJ) -fPIC -shared -o libft_malloc_$(HOSTTYPE).so
	ln -sf libft_malloc_$(HOSTTYPE).so libft_malloc.so

%.o: %.c
	gcc $(CFLAGS) -c $< -I./includes -o $@

clean:
	echo "\033[1;31m" "DELETE FILES MALLOC" "\033[0m"
	rm -f $(OBJ)

fclean: clean
	echo "\033[1;31m" "DELETE MALLOC.SO" "\033[0m"
	rm -f libft_malloc.so
	rm -f libft_malloc_$(HOSTTYPE).so

test: all
	cp libft_malloc.so test/.
	cp includes/ft_malloc.h test/.

re: fclean all
