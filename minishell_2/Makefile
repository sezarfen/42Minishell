SRCS = main.c utils.c  cleaner.c 
CONTROLLERS = controllers/controllers.c controllers/is_special.c controllers/is_special2.c
LEXER_PARSER = lexer_parser/parser2.c lexer_parser/lexer.c
BUILTINS =	builtins/cd.c builtins/export.c builtins/pwd.c
all:
	gcc -o minishell $(SRCS) $(CONTROLLERS) $(LEXER_PARSER) $(BUILTINS) -lreadline libft/libft.a