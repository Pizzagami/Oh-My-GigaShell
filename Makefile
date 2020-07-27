NAME = minishell

LIB = libft.a

SRCS = ./srcs/main.c	\
	   ./srcs/bashy.c	\
	   ./srcs/term_init.c

FLAG = -L includes/libft

CFLAGS = -Wall -Wextra -Werror -I includes/ -I includes/libft/ -fsanitize=address	

CC = gcc

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(FLAG) $(CFLAGS) $(OBJS)  ./includes/libft/libft.a


lib:
	make -C ./includes/libft re
	make -C ./includes/libft clean
clean:
	${RM} $(OBJS)

fclean: clean
	${RM} $(NAME)

re: fclean all
	${RM} $(OBJS)

.PHONY: all clean fclean re lib
