# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amugnier <amugnier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/30 17:55:30 by amugnier          #+#    #+#              #
#    Updated: 2024/01/08 15:56:05 by amugnier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

PATH_HEADER = includes
PATH_SRCS = srcs
OBJ_DIR = .objs

HDRS = $(PATH_HEADER)/libft.h \
	   $(PATH_HEADER)/get_next_line.h \
	   $(PATH_HEADER)/ft_printf.h \

SRCS = $(PATH_SRCS)/ft_atoi.c \
	  $(PATH_SRCS)/ft_bzero.c \
	  $(PATH_SRCS)/ft_calloc.c \
	  $(PATH_SRCS)/ft_isalnum.c \
	  $(PATH_SRCS)/ft_isalpha.c \
	  $(PATH_SRCS)/ft_isascii.c \
	  $(PATH_SRCS)/ft_isdigit.c \
	  $(PATH_SRCS)/ft_isprint.c \
	  $(PATH_SRCS)/ft_itoa.c \
	  $(PATH_SRCS)/ft_uitoa.c \
	  $(PATH_SRCS)/ft_memchr.c \
	  $(PATH_SRCS)/ft_memcmp.c \
	  $(PATH_SRCS)/ft_memcpy.c \
	  $(PATH_SRCS)/ft_memmove.c \
	  $(PATH_SRCS)/ft_memset.c \
	  $(PATH_SRCS)/ft_putchar_fd.c \
	  $(PATH_SRCS)/ft_putendl_fd.c \
	  $(PATH_SRCS)/ft_putnbr_fd.c \
	  $(PATH_SRCS)/ft_putstr_fd.c \
	  $(PATH_SRCS)/ft_split.c \
	  $(PATH_SRCS)/ft_strchr.c \
	  $(PATH_SRCS)/ft_strdup.c \
	  $(PATH_SRCS)/ft_striteri.c \
	  $(PATH_SRCS)/ft_strjoin.c \
	  $(PATH_SRCS)/ft_strlcat.c \
	  $(PATH_SRCS)/ft_strlcpy.c \
	  $(PATH_SRCS)/ft_strlen.c \
	  $(PATH_SRCS)/ft_strmapi.c \
	  $(PATH_SRCS)/ft_strncmp.c \
	  $(PATH_SRCS)/ft_strnstr.c \
	  $(PATH_SRCS)/ft_strrchr.c \
	  $(PATH_SRCS)/ft_strtrim.c \
	  $(PATH_SRCS)/ft_substr.c \
	  $(PATH_SRCS)/ft_tolower.c \
	  $(PATH_SRCS)/ft_toupper.c \
	  $(PATH_SRCS)/get_next_line.c \
	  $(PATH_SRCS)/get_next_line_utils.c \
	  $(PATH_SRCS)/ft_lstadd_back.c \
	  $(PATH_SRCS)/ft_lstadd_front.c \
	  $(PATH_SRCS)/ft_lstclear.c \
	  $(PATH_SRCS)/ft_lstdelone.c \
	  $(PATH_SRCS)/ft_lstiter.c \
	  $(PATH_SRCS)/ft_lstlast.c \
	  $(PATH_SRCS)/ft_lstmap.c \
	  $(PATH_SRCS)/ft_lstnew.c \
	  $(PATH_SRCS)/ft_lstsize.c \
	  $(PATH_SRCS)/ft_printf.c \
	  $(PATH_SRCS)/ft_printf_utils.c \
	  $(PATH_SRCS)/ft_put_pointer.c \
	  $(PATH_SRCS)/ft_strstr.c \
	  $(PATH_SRCS)/ft_issign.c \
	  $(PATH_SRCS)/ft_nb_abs.c \

OBJS = $(patsubst $(PATH_SRCS)/%.c, $(OBJ_DIR)/%.o, $(SRCS))


$(OBJ_DIR)/%.o: $(PATH_SRCS)/%.c $(HDRS)
	@mkdir -p $(OBJ_DIR)
	cc $(FLAGS) -c $< -o $@ -I $(PATH_HEADER)

FLAGS = -Wall -Werror -Wextra -g3

OPTION = -c

.c.o:
	cc $(FLAGS) $(OPTION) $< -o $(<:.c=.o) -I $(PATH_HEADER)

$(NAME): $(OBJS)
	ar rcs -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJ) $(OBJS_BONUS)
	rm -rf $(OBJ_DIR)


fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
