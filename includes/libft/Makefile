# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pizzagami <pizzagami@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 11:50:27 by braimbau          #+#    #+#              #
#    Updated: 2020/11/26 12:26:58 by pizzagami        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =  ./ft_atoi.c			\
        ./ft_isalpha.c		\
        ./ft_itoa.c			\
        ./ft_memcpy.c		\
        ./ft_putendl_fd.c	\
        ./ft_strchr.c		\
        ./ft_strnstr.c		\
        ./ft_tolower.c		\
        ./ft_bzero.c		\
        ./ft_isascii.c		\
        ./ft_memccpy.c		\
        ./ft_memmove.c		\
        ./ft_putnbr_fd.c	\
        ./ft_strdup.c		\
        ./ft_strlen.c		\
        ./ft_strrchr.c		\
        ./ft_toupper.c		\
        ./ft_calloc.c		\
        ./ft_isdigit.c		\
        ./ft_memchr.c		\
        ./ft_strfind.c      \
        ./ft_memset.c		\
        ./ft_putstr_fd.c	\
        ./ft_strjoin.c		\
        ./ft_strmapi.c		\
        ./ft_strtrim.c		\
        ./ft_isalnum.c		\
        ./ft_isprint.c		\
        ./ft_memcmp.c		\
        ./ft_putchar_fd.c	\
        ./ft_split.c		\
        ./ft_strlcat.c		\
		./ft_strcmp.c		\
        ./ft_strncmp.c		\
        ./ft_substr.c		\
        ./ft_strlcpy.c		\
		./ft_putstr.c       \
		./ft_findstr.c		\
        ./get_next_line.c   \
        ./get_next_line_utils.c


OBJ = $(SRCS:.c=.o)

OBJ_BONUS = $(OBJ)

CFLAGS += -Wall -Wextra -Werror -fsanitize=address -g3 -I./includes

all: $(NAME)

$(NAME)	:	$(OBJ)
	ar rc	$(NAME) $(OBJ)
	ranlib	$(NAME)

clean:
	rm -f $(OBJ_BONUS)

fclean : clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJ_BONUS)
	ar rc $(NAME) $(OBJ_BONUS)
	ranlib $(NAME)

.PHONY: all re clean fclean bonus
