NAME = minishell

LIB = libft.a

FLAG = -Wall -Wextra -Werror

SRCS = ./builtin/builtin_pwd.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIB)
	gcc -o $(NAME) $(FLAG) $(SRCS) -L./includes/libft

$(LIB):
	make -C ./includes/libft re
 
clean:
	make -C ./includes/libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all


