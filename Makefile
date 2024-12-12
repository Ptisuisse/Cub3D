# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 12:03:43 by dpoltura          #+#    #+#              #
#    Updated: 2024/12/12 15:05:31 by dpoltura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Wextra -Werror -g

SRCS =	utils.c \
		utils_bis.c \
		parse.c \
		init_texture.c \
		init_texture_bis.c \
		init_color.c \
		init_color_bis.c \
		parse_map.c \
		parse_map_bis.c \
    	main.c \
		mlx_init.c \
		mini_map.c \
		raycasting.c \
		parse_map_ter.c

GNL_SRCS =	get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c

OBJS = $(SRCS:%.c=%.o)

GNL_OBJS = $(GNL_SRCS:%.c=%.o)

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

NAME = cub3d

all: $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS)
	make -C $(MLX_DIR)
	$(CC) $(OBJS) $(GNL_OBJS) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -o $(NAME)

clean:
	make clean -C $(MLX_DIR)
	rm $(OBJS) $(GNL_OBJS)

fclean: clean
	rm $(NAME)

re: fclean all
