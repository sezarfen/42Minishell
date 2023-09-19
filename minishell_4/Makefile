NAME = minishell
LIBFT = libft/libft.a
SRCS = main.c utils.c set_executable.c
CONTROLLERS = controllers/controllers.c controllers/is_special.c controllers/is_special2.c
LEXER_PARSER = lexer_parser/parser.c lexer_parser/lexer.c lexer_parser/parser_utils.c
BUILTINS =	builtins/cd.c builtins/export.c builtins/pwd.c builtins/unset.c builtins/env_builtin.c builtins/echo.c builtins/exit.c
CLEANERS = cleaners/cleaner.c cleaners/cleaner_parser.c cleaners/ft_strdup_impr.c
EXECUTER = executer/to_execute.c
OBJS = $(SRCS:.c=.o) $(CONTROLLERS:.c=.o) $(LEXER_PARSER:.c=.o) $(BUILTINS:.c=.o) $(CLEANERS:.c=.o) $(EXECUTER:.c=.o)
CC = gcc

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	gcc -o minishell $(OBJS) -lreadline libft/libft.a

$(LIBFT):
	make -C libft

clean:
	rm -rf *.o
	rm -rf */*.o
	make -C libft clean

fclean: clean
	rm -rf minishell
	make -C libft fclean

.PHONY: all