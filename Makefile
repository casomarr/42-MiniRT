# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: casomarr <casomarr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 12:03:11 by amugnier          #+#    #+#              #
#    Updated: 2024/02/09 20:33:19 by casomarr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



# **************************************************************************** #
#                                  CONFIGURATION                               #
# **************************************************************************** #

NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra
#-g3 -gdwarf-4
CFLAGS+= -Werror
LINKER_FLAGS = -lXext -lX11 -lm

PATH_LIBFT = libft
PATH_INCLUDE = includes
PATH_SRCS = srcs
PATH_RENDER = render
PATH_PARSING = parsing
PATH_MATHS = maths
PATH_MLX = mlx

RM = rm -f

# **************************************************************************** #
#                                  DEPENDANCIES                                #
# **************************************************************************** #

### LIBRAIRIES
LIBFT = $(PATH_LIBFT)/libft.a

MLX = $(PATH_MLX)/libmlx.a

### HEADERS
HDRS = $(PATH_INCLUDE)/minirt.h \

### SOURCES
SRCS =   $(PATH_SRCS)/main.c \
	   $(PATH_SRCS)/$(PATH_PARSING)/check_objs.c \
	   $(PATH_SRCS)/$(PATH_PARSING)/check_data_objs.c \
	   $(PATH_SRCS)/$(PATH_PARSING)/open_file.c \
	   $(PATH_SRCS)/$(PATH_PARSING)/parse_file.c \
	   $(PATH_SRCS)/$(PATH_PARSING)/check_params.c \
	   $(PATH_SRCS)/$(PATH_PARSING)/set_data.c \
	   $(PATH_SRCS)/$(PATH_PARSING)/init.c \
	   $(PATH_SRCS)/$(PATH_PARSING)/check_data_objs2.c \
	   $(PATH_SRCS)/$(PATH_PARSING)/parsing_utils.c \
	   $(PATH_SRCS)/$(PATH_PARSING)/set_objs.c \
	   $(PATH_SRCS)/$(PATH_PARSING)/set_objs2.c \
	   $(PATH_SRCS)/$(PATH_PARSING)/check_objs_shape.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/color.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/cylinder.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/cylinder_check_hit.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/intersections.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/light_attenuation.c \
  	   $(PATH_SRCS)/$(PATH_RENDER)/plane.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/rays.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/render.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/sphere.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/utils.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/$(PATH_MATHS)/add_substract_maths.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/$(PATH_MATHS)/compare_maths.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/$(PATH_MATHS)/dot_maths.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/$(PATH_MATHS)/multiply_divide_maths.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/$(PATH_MATHS)/norm_maths.c \
	   $(PATH_SRCS)/$(PATH_RENDER)/$(PATH_MATHS)/sqrt_maths.c \

SRCS_PARSING = $(PATH_SRCS)/check_objs.c \
	   $(PATH_SRCS)/check_data_objs.c \
	   $(PATH_SRCS)/open_file.c \
	   $(PATH_SRCS)/parse_file.c \
	   $(PATH_SRCS)/parsing.c

### DIRECTORIES & FILES
OBJ_DIR = .objs


OBJS = $(patsubst $(PATH_SRCS)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

OBJS_PARSING = $(patsubst $(PATH_SRCS)/%.c, $(OBJ_DIR)/%.o, $(SRCS_PARSING))

# **************************************************************************** #
#                                  COMPILATION                                 #
# **************************************************************************** #

### RULES OF COMPILATION
$(OBJ_DIR)/%.o: $(PATH_SRCS)/%.c $(HDRS)
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(PATH_PARSING) $(OBJ_DIR)/$(PATH_RENDER) $(OBJ_DIR)/$(PATH_RENDER)/$(PATH_MATHS)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(PATH_MLX) -I $(PATH_LIBFT)/$(PATH_INCLUDE) -I $(PATH_SRCS) -I $(PATH_INCLUDE)

# **************************************************************************** #
#                                  MAIN TARGET                                 #
# **************************************************************************** #

### BUILD
all: $(LIBFT) $(MLX) $(NAME)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LINKER_FLAGS) $(MLX)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(PATH_MLX) -I $(PATH_LIBFT) -I $(PATH_SRCS)

### LIBFT

$(LIBFT):
	$(MAKE) -C $(PATH_LIBFT)

### MLX
$(MLX):
	$(MAKE) -C $(PATH_MLX)

### CLEANING
clean:
	$(MAKE) -C $(PATH_LIBFT) clean
	$(MAKE) -C $(PATH_MLX) clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(PATH_LIBFT) fclean
	$(RM) $(NAME)
	$(RM) $(GTACTION)

### REBUILD
re: fclean all


# **************************************************************************** #
#                                  GITHUB ACTION                               #
# **************************************************************************** #

### NAME OF GITHUB ACTION
GTACTION = minirt_action

SRCS_ACTION = $(PATH_SRCS)/check_compile.c
HDRS_ACTION = $(PATH_INCLUDE)/check_compile.h


OBJS_DIR_ACTION = .objs_action
OBJS_ACTIONS = $(patsubst $(PATH_SRCS)/%.c, $(OBJS_DIR_ACTION)/%.o, $(SRCS_ACTION))


$(OBJS_DIR_ACTION)/%.o: $(PATH_SRCS)/%.c $(HDRS_ACTION)
	@mkdir -p $(OBJS_DIR_ACTION)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(PATH_MLX) -I $(PATH_LIBFT)/$(PATH_INCLUDE) -I $(PATH_SRCS) -I $(PATH_INCLUDE)

$(GTACTION): $(OBJS_ACTIONS)
	$(CC) $(CFLAGS) -o $(GTACTION) $(OBJS_ACTIONS) $(LIBFT) $(LINKER_FLAGS) $(MLX)

# action: $(LIBFT) $(MLX) $(GTACTION)

#remove $(MLX) From $(NAME) if parsing are call by make parsing
# parsing: $(LIBFT) $(OBJS_PARSING)
# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJS_PARSING) $(LIBFT)

# **************************************************************************** #
#                                   PHONIES                                    #
# **************************************************************************** #

.PHONY: all clean fclean re action parsing
