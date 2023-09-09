#ifndef MINISHELL_H
# define MINISHELL_H

typedef	struct s_lexer
{
	char	**tokens;
	int		size;
}	t_lexer;

typedef struct s_parser
{
	char	**cmds;
	int		stdin;
	int		stdout;
}	t_parser;

typedef	struct s_env
{
	char	**key;
	char	**value;
}	t_env;

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h> // don't forget to use with -lreadline // it could be library-readline
# include <readline/history.h>
# include <signal.h>

int		split_len(char **split);
char	**the_lexer(char *str);
int		equal_len(char *str);

#endif