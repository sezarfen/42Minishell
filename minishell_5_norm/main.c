/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:10:50 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 14:10:50 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exitstatus;

/*
Function: int rl_on_new_line (void)
	Tell the update functions that
	we have moved onto a new (empty) line,
 	usually after outputting a newline.

Function: void rl_redisplay (void)
	Change what’s displayed on the
	screen to reflect the current
	contents of rl_line_buffer.

Function: void rl_replace_line (const char *text, int clear_undo)
	Replace the contents of rl_line_buffer with text.
	The point and mark are preserved, if possible.
	If clear_undo is non-zero, the undo list 
	associated with the current line is cleared.

*/
void	default_sigint(int sig)
{
	(void)sig;
	g_exitstatus = 130;
	printf("\n");
	rl_on_new_line();
	//rl_replace_line("", 1);
	rl_redisplay();
}

t_lexer	*init_lexer(void)
{
	t_lexer	*tlexer;
	char	*str;
	char	*prompt;

	prompt = set_propmt();
	str = readline(prompt);
	if (!str)
	{
		free(prompt);
		write(1, "\033[D\033[D", 7);
		printf("exit\n");
		exit(1);
	}
	add_history(str);
	tlexer = malloc(sizeof(t_lexer));
	tlexer->tokens = the_lexer(str, 0, 0, 0);
	tlexer->size = split_len(tlexer->tokens);
	free(str);
	free(prompt);
	return (tlexer);
}

t_env	*set_env(char **the_env, int f)
{
	t_env	*env;
	int		len;
	int		i;

	len = split_len(the_env);
	env = malloc(sizeof(t_env));
	env->key = ft_calloc(sizeof(char *), (len + 1 + f));
	env->value = ft_calloc(sizeof(char *), (len + 1 + f));
	i = 0;
	while (the_env[i])
	{
		env->key[i] = ft_substr(the_env[i], 0, equal_len(the_env[i]));
		env->value[i] = ft_substr(the_env[i],
				equal_len(the_env[i]) + 1, ft_strlen(the_env[i]));
		i++;
	}
	if (f == 1)
	{
		env->key[i] = ft_strdup("?");
		env->value[i] = ft_strdup("0");
	}
	return (env);
}

t_ee	*set_env_exp(char **the_env)
{
	t_ee	*env_exp;

	env_exp = malloc(sizeof(t_ee));
	env_exp->env = set_env(the_env, 1);
	env_exp->penv = set_env(the_env, 0);
	return (env_exp);
}

int	main(int ac, char **av, char **the_env)
{
	t_lexer			*lexer;
	t_parser		*parser;
	t_ee			*env_exp;

	if (ac == 2)
		check_av(av);
	env_exp = set_env_exp(the_env);
	g_exitstatus = 0;
	signal(SIGINT, default_sigint);
	while (1)
	{
		lexer = init_lexer();
		if (lexer->tokens[0] == NULL || lexer_control(lexer, -1))
		{
			continue ;
		}
		parser = set_parser(lexer, 0, 0);
		fill_parser(parser, env_exp->env, 0, 0);
		free_lexer(lexer);
		to_execute(parser, the_env, &env_exp);
		free_parser(parser);
		//system("leaks minishell");
	}
	return (0);
}
