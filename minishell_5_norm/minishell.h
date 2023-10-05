/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:10:46 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 14:10:46 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_lexer
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
	int				hd_in;
	int				dollar_command;
	struct s_parser	*next;
}	t_parser;

typedef struct s_env
{
	char	**key;
	char	**value;
	char	*clean;
}	t_env;

typedef struct s_ee
{
	struct s_env	*env;
	struct s_env	*penv;
}	t_ee;

extern int	g_exitstatus;

int			split_len(char **split);
char		**the_lexer(char *str, int i, int k, int f);
int			equal_len(char *str);
void		free_split(char **split);
void		print_split(char **split);
t_parser	*set_parser(t_lexer *lexer, int i, int k);
char		*cleaner(char *str, t_env *env, int i, int k);
int			lexer_control(t_lexer *lexer, int i);
int			is_special(char *str);
int			is_pipe(char *str);
int			is_output_redirect(char *str);
int			is_input_redirect(char *str);
int			is_builtin(char *str);
int			is_heredoc(char *str);
int			is_append(char *str);
int			is_redirects(char *str);
void		cd(int argc, char *args, t_ee **ee);
void		pwd(void);
void		print_env(t_env *env);
void		export(char **cmds, t_env **env, t_env **penv, int i);
void		free_env(t_env *exp);
void		unset(char *element, t_env **env);
void		redirect_cleaner(t_parser *parser, int i, int k);
void		input_cleaner(t_parser *parser, int i, int k);
char		*ft_strdup_impr(const char *s1);
char		*get_value_by_key(char *key, t_env *env);
void		clean_and_set_exec(t_parser *parser, t_env *env);
void		fill_parser(t_parser *parser, t_env *env, int i, int a);
void		input_redirect(t_parser *parser, int i);
void		output_redirect(t_parser *parser, int i);
void		open_in_append(t_parser *parser, int i);
void		clean_parser(t_parser *parser, t_env *env);
void		to_execute(t_parser *parser, char **env, t_ee **envexp);
int			get_max(int a, int b);
char		*set_propmt(void);
void		env_builtin(t_env *env);
void		echo(t_parser *parser);
int			parser_len(t_parser *parser);
void		exit_builtin(t_parser *parser);
int			ft_isfulldigit(char *str);
void		add_to_env(t_env **env, char *key, char *value);
int			ft_strcmp(char *s1, char *s2);
int			ft_iscontain(char *str, char c);
void		print_exp(t_env *penv);
void		free_lexer(t_lexer *lexer);
void		free_parser(t_parser *parser);
void		free_ee(t_ee *ee);
char		*ft_strjoin_df(char const *s1, char const *s2);
void		set_exec(t_parser *parser, t_env *env);
void		add_to_penv(char *str, t_env **penv);
char		**set_exec_args(t_parser *parser);
void		dup_redirections(t_parser *parser);
void		close_files(t_parser *parser);
void		close_file(t_parser *parser);
void		set_pipe(int fd[], int i, int len);
void		execute_builtin(t_parser *parser, t_ee **ee);
void		child_builtins(t_parser *parser, t_ee **ee);
void		count_quotes(char *str, int i, int j, int k);
void		check_dollar_command(t_parser *parser, t_env *env);
char		*set_filename(int a);
void		expand_dollar(t_parser *parser, t_env *env);
void		set_heredoc(t_parser *parser, int i, int a);
void		check_av(char **av);

#endif