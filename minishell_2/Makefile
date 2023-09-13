SRCS = main.c utils.c set_executable.c
CONTROLLERS = controllers/controllers.c controllers/is_special.c controllers/is_special2.c
LEXER_PARSER = lexer_parser/parser2.c lexer_parser/lexer.c
BUILTINS =	builtins/cd.c builtins/export.c builtins/pwd.c builtins/unset.c
CLEANERS = cleaners/cleaner.c cleaners/cleaner_parser.c cleaners/ft_strdup_impr.c
all:
	gcc -o minishell $(SRCS) $(CONTROLLERS) $(LEXER_PARSER) $(BUILTINS) $(CLEANERS) -lreadline libft/libft.a