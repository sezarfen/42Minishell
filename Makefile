NAME = minishell

CC = @gcc
CFLAGS = -Werror -Wall -Wextra #-g -fsanitize=address

LIBFT = libft/libft.a
SRCS = main.c set_executable.c
CONTROLLERS = controllers/controllers.c controllers/is_special.c controllers/is_special2.c signals.c
LEXER_PARSER = lexer_parser/parser.c lexer_parser/lexer.c lexer_parser/parser_utils.c lexer_parser/parser_utils2.c
BUILTINS =	builtins/cd.c builtins/export.c builtins/pwd.c builtins/unset.c builtins/env_builtin.c builtins/echo.c builtins/exit.c
CLEANERS = cleaners/cleaner.c cleaners/cleaner_parser.c cleaners/ft_strdup_impr.c
EXECUTER = executer/to_execute.c executer/execute_utils.c executer/execute_utils2.c
UTILS = utils/utils.c utils/utils2.c utils/utils3.c utils/utils4.c utils/utils5.c
OBJS = $(SRCS:.c=.o) $(CONTROLLERS:.c=.o) $(LEXER_PARSER:.c=.o) \
		$(BUILTINS:.c=.o) $(CLEANERS:.c=.o) $(EXECUTER:.c=.o) $(UTILS:.c=.o)

LINKERS = -lreadline -L ./lib/lib/readline/lib
INCLUDES = -I. -I ./lib/lib/readline/include

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo	Compilation on progress...
	@gcc $(CFLAGS) -o minishell $(OBJS) -lreadline libft/libft.a
	@echo	Compilation DONE!...

$(LIBFT):
	make -C libft

clean:
	@rm -rf *.o
	@rm -rf */*.o
	@make -C libft clean
	@echo All files are cleaned!

fclean: clean
	@rm -rf minishell
	@make -C libft fclean
	@echo All files are fully-cleaned!

re: fclean all

.PHONY: all clean fclean all