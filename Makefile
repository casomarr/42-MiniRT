# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 12:47:48 by amugnier          #+#    #+#              #
#    Updated: 2023/12/06 17:29:33 by amugnier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LINKER_FLAGS = -lXext -lX11 -lm

PATH_LIBFT = libft
PATH_INCLUDE = includes
PATH_SRCS = srcs
PATH_MLX = mlx


LIBFT = $(PATH_LIBFT)/libft.a

MLX = $(PATH_MLX)/libmlx.a

HDRS = $(PATH_INCLUDE)/minirt.h \

SRCS = $(PATH_SRCS)/main.c \


OBJ_DIR = .objs

OBJS = $(patsubst $(PATH_SRCS)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

RM = rm -f

$(OBJ_DIR)/%.o: $(PATH_SRCS)/%.c $(HDRS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(PATH_MLX) -I $(PATH_LIBFT)/$(PATH_INCLUDE) -I $(PATH_SRCS) -I $(PATH_INCLUDE)


all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LINKER_FLAGS) $(MLX)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(PATH_MLX) -I $(PATH_LIBFT) -I $(PATH_SRCS)

$(LIBFT):
	$(MAKE) -C $(PATH_LIBFT)

$(MLX):
	$(MAKE) -C $(PATH_MLX)

clean:
	$(MAKE) -C $(PATH_LIBFT) clean
	$(MAKE) -C $(PATH_MLX) clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(PATH_LIBFT) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
