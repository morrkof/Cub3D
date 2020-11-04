# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/03 16:22:35 by ppipes            #+#    #+#              #
#    Updated: 2020/11/04 18:14:19 by ppipes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRC = bmp.c sprites.c utils.c cub.c angle.c draw.c color.c\
 map.c textures.c parameters.c calculate.c key.c draw_utils.c minimap.c
HEADER = ./cub.h
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror 
LIBFLAGS = -Lmlx_linux -lmlx_Linux -Llibft -lft -lXext -lX11 -lm 
LIBFT = ./libft/libft.a
LIBMLX = ./mlx_linux/libmlx_Linux.a

.PHONY: all clean fclean re empty

all: $(NAME)
$(NAME): $(OBJ) $(HEADER) $(LIBFT) $(LIBMLX)
	gcc $(OBJ) $(LIBFLAGS) $(CFLAGS) -o $(NAME)
%.o: %.c
	gcc $(CFLAGS) -c $<
$(LIBFT): empty
	$(MAKE) -C ./libft
$(LIBMLX):
	$(MAKE) -C ./mlx_linux
clean:
	$(MAKE) -C ./libft clean
	$(MAKE) -C ./mlx_linux clean
	rm -rf $(OBJ)
fclean: clean
	$(MAKE) -C ./libft fclean
	rm -rf $(NAME) screenshot.bmp
re: fclean all
empty: 
