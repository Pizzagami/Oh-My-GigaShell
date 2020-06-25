NAME = minishell

LIB = libft.a

SRCS = ./srcs/main.c	\
	   ./srcs/bashy.c	\
	   ./srcs/term_init.c

FLAG = -L includes/libft -Wall -Wextra -Werror

CFLAGS = -Wall -Wextra -Werror -I includes/ -I includes/libft/	

CC = gcc

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(FLAG) $(CFLAGS) $(OBJS)  ./includes/libft/libft.a


lib:
	make -C ./includes/libft re
 
clean:
	${RM} $(OBJS)

fclean: clean
	${RM} $(NAME)

re: fclean all
	${RM} $(OBJS)

.PHONY: all clean fclean re lib
