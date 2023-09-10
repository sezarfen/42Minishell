all:
	gcc -o minishell main.c parser.c utils.c lexer.c cleaner.c -lreadline libft/libft.a   