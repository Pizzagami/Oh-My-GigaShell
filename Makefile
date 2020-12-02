NAME = minishell

LIB = libft.a

SRCS =	./srcs/main.c					\
		./srcs/bashy.c					\
		./srcs/term_init.c				\
		./srcs/tools.c					\
		./srcs/tools_env.c  		    \
	   	./srcs/persecutor.c 			\
		./srcs/display_tree.c 			\
		./srcs/display_tree2.c			\
		./srcs/exec_tree.c				\
		./srcs/exec_tree2.c 			\
		./srcs/fd_gestion.c 			\
		./srcs/parse_andor.c 			\
		./srcs/parse_command.c 			\
		./srcs/parse_input.c 			\
		./srcs/parse_instruction.c 		\
		./srcs/parse_list.c 			\
		./srcs/parse_pipeline.c 		\
		./srcs/parse_redirection.c 		\
		./srcs/parser_clean.c 			\
		./srcs/parser_clean2.c 			\
		./srcs/parser_tools.c 			\
		./srcs/token_creation.c 		\
		./srcs/token_creation_utils.c 	\
		./srcs/token_tools.c 			\
		./srcs/exec.c 					\
		./srcs/get_env.c				\
		./srcs/env.c 					\
		./srcs/colors.c					\
		./srcs/star.c					\
		./srcs/exec_builtin.c			\
		./srcs/quote_string.c			\
		./builtin/builtin_cd.c			\
		./builtin/builtin_pwd.c			\
		./builtin/builtin_env.c			\
		./builtin/builtin_echo.c			\

FLAG = -L includes/libft
FSANITIZE = -fsanitize=address -g3
CFLAGS = -Wall -Wextra -Werror -I includes/ -I includes/libft/ $(FSANITIZE)	

CC = gcc

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(FLAG) $(OBJS) ./includes/libft/libft.a


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
