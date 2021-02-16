NAME = minishell

LIB = libft.a

SRCS =	./srcs/main.c							\
		./srcs/bashy/bashy.c					\
		./srcs/bashy/bashy_direction.c			\
		./srcs/bashy/bashy_utils.c				\
		./srcs/bashy/bashy_tools.c				\
		./srcs/bashy/bashy_poor.c				\
		./srcs/bashy/bashy_tools_dir.c			\
		./srcs/star/star_utils.c				\
		./srcs/star/star_list_gestion.c			\
		./srcs/star/star_some_stuff.c			\
		./srcs/star/star_random_utils.c			\
		./srcs/star/star_char_editing.c			\
		./srcs/parse/parse_andor.c 				\
		./srcs/parse/parse_command.c 			\
		./srcs/parse/parse_input.c 				\
		./srcs/parse/parse_instruction.c 		\
		./srcs/parse/parse_list.c 				\
		./srcs/parse/parse_pipeline.c 			\
		./srcs/parse/parse_redirection.c 		\
		./srcs/parse/parser_clean.c 			\
		./srcs/parse/parser_clean2.c 			\
		./srcs/parse/parser_tools.c 			\
		./srcs/token/token_creation.c 			\
		./srcs/token/token_creation_utils.c 	\
		./srcs/token/token_tools.c 				\
		./srcs/exec/exec.c 						\
		./srcs/exec/exec_tree.c					\
		./srcs/exec/exec_tree2.c 				\
		./srcs/exec/exec_utils.c				\
		./srcs/exec/exec_redirection.c			\
		./srcs/env/tools_env.c  			    \
		./srcs/env/split_env.c					\
		./srcs/env/get_env.c					\
		./srcs/env/env.c 						\
		./srcs/star/star.c						\
		./srcs/exec/exec_builtin.c				\
		./srcs/quote/quote_string.c				\
		./srcs/quote/quote_utils.c				\
		./srcs/quote/quote_char_edit.c			\
		./srcs/sunob/heredoc.c						\
		./srcs/sunob/heredoc_tree.c					\
		./srcs/sunob/colors.c					\
		./srcs/sunob/term_init.c				\
		./srcs/sunob/multilines.c				\
		./srcs/sunob/file_histo.c				\
		./srcs/grand_remplacement.c				\
		./srcs/tools.c							\
	   	./srcs/persecutor.c 					\
		./srcs/display_tree.c 					\
		./srcs/display_tree2.c					\
		./srcs/fd_gestion.c 					\
		./builtin/builtin_cd.c					\
		./builtin/builtin_pwd.c					\
		./builtin/builtin_env.c					\
		./builtin/builtin_echo.c				\
		./builtin/builtin_exit.c				\

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
