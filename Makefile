# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/10 17:12:08 by nildruon          #+#    #+#              #
#    Updated: 2026/04/03 07:45:25 by nildruon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Werror -Wall -Wextra -g -Ilibft_lib 

FDFFLAGS = -L. -lmlx -lXext -lX11 -lm

CFILES = src/calculations_for_projections/calculations.c src/calculations_for_projections/calculations_help.c \
		src/extract_data/extract_data.c src/extract_data/extract_data_help.c \
		src/graphics/draw_full_img.c src/graphics/draw_line.c \
		src/win_main.c src/main.c

OFILES = $(CFILES:.c=.o)


NAME = fdf

HEADER = fdf.h

LIBFT = libft_lib
LIBFT_A = $(LIBFT)/libft.a
CREATE = ar rcs

REMOVE = rm -f


%.o: %.c  $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OFILES) $(LIBFT_A) $(FDFFLAGS) -o $(NAME)

fclean: clean
	$(REMOVE) $(NAME)
	@make -C $(LIBFT) fclean

clean:
	$(REMOVE) $(OFILES)
	@make -C $(LIBFT) clean

re: fclean all

.PHONY: all clean fclean re