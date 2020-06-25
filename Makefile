NAME = minishell

LIB = libft.a

FLAG = -Wall -Wextra -Werror

CFLAGS = -Wall -Wextra -Werror -I includes/ -I includes/libft

SRCS = ./srcs/*.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	gcc -o $(NAME) $(FLAG) $(OBJS)

lib:
	make -C ./includes/libft re
 
clean:
	make -C ./includes/libft clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
	rm -rf $(OBJS)

.PHONY: all clean fclean re lib
