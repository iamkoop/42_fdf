# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nildruon <nildruon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/10 17:12:08 by nildruon          #+#    #+#              #
#    Updated: 2026/03/25 17:03:02 by nildruon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Werror -Wall -Wextra -g -Ilibft_lib 

FDFFLAGS = -L. -lmlx -lXext -lX11 -lm

CFILES = draw_full_img.c draw_line.c projection.c extract_data.c extract_data_help.c main.c

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