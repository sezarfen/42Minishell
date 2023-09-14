#ifndef MINISHELL_H
# define MINISHELL_H

typedef	struct s_lexer
{
	char	**tokens;
	int		size;
}	t_lexer;

typedef struct s_parser
{
	char			**cmds;
	int				fd_in;
	int				fd_out;
	int				is_builtin;
	struct s_parser *next;
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

int			split_len(char **split);
char		**the_lexer(char *str, int i, int k, int f);
int			equal_len(char *str);
void		free_split(char **split);
t_parser	*set_parser(t_lexer *lexer);
char		*cleaner(char *str, t_env *env);
void		lexer_control(t_lexer *lexer);
int			is_special(char *str);
int			is_pipe(char *str);
int			is_output_redirect(char *str);
int			is_input_redirect(char *str);
int			is_builtin(char *str);
void		cd(int argc, char *args);
void		pwd(void);
void	 	print_env(t_env *env);
t_env		*export(char *str, t_env *env, t_env *exp);
void		free_env(t_env *exp);
t_env		*unset(char *element, t_env *env);
void		output_cleaner(t_parser *parser);
void		input_cleaner(t_parser *parser);
char		*ft_strdup_impr(const char *s1);
char		*get_value_by_key(char *key, t_env *env);
void		set_right_exec(t_parser *parser);


#endif