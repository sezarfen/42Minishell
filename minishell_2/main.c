#include "minishell.h"

void	output_redirect(t_parser *parser, int i)
{
	parser->fd_out = open(parser->cmds[i + 1], O_CREAT | O_RDWR);
	if (parser->fd_out == -1)
		printf("cannot open that file...");
}

void	input_redirect(t_parser *parser, int i)
{
	parser->fd_in = open(parser->cmds[i - 1], O_CREAT | O_RDWR);
	if (parser->fd_out == -1)
		printf("cannot open that file...");
}

void	fill_parser(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser)
	{
		parser->is_builtin = is_builtin(parser->cmds[0]);
		while (parser->cmds[i])
		{
			if (is_output_redirect(parser->cmds[i]))
				output_redirect(parser, i);
			else if (is_input_redirect(parser->cmds[i]))
				input_redirect(parser, i);
			i++;
		}
		i = 0;
		parser = parser->next;
	}
}

t_lexer	*init_lexer(void)
{
	t_lexer	*tlexer;
	char	*str;

	str = readline("minishell$ ");
	tlexer = malloc(sizeof(t_lexer));
	tlexer->tokens = the_lexer(str);
	tlexer->size = split_len(tlexer->tokens);
	free(str);
	return (tlexer);
}

t_env	*set_env(char **the_env)
{
	t_env	*env;
	int		len;
	int		i;

	len = split_len(the_env);
	env = malloc(sizeof(t_env));
	env->key = ft_calloc(sizeof(char *), (len + 1));
	env->value = ft_calloc(sizeof(char *), (len + 1));
	i = 0;
	while (the_env[i])
	{
		env->key[i] = ft_substr(the_env[i], 0, equal_len(the_env[i]));
		env->value[i] = ft_substr(the_env[i], equal_len(the_env[i]) + 1, ft_strlen(the_env[i]));
		i++;
	}
	return (env);
}

int main(int ac, char **av, char **the_env)
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_env		*env_list;
	t_env		*exp_list;

	//lexer_control(lexer);
	env_list = set_env(the_env);
	exp_list = set_env(the_env);
	while (1)
	{
		lexer = init_lexer();
		parser = set_parser(lexer);
		fill_parser(parser);
		if (!ft_strncmp(lexer->tokens[0], "export", ft_strlen(lexer->tokens[0])))
			env_list = export(lexer->tokens[1], env_list);
		if (!ft_strncmp(lexer->tokens[0], "env", ft_strlen(lexer->tokens[0])))
			print_env(env_list);
		if (!ft_strncmp(lexer->tokens[0], "unset", ft_strlen(lexer->tokens[0])))
			unset(lexer->tokens[1], env_list);
	}
	return (0);
}


/*
		LEXER İÇERİKLERİNİ CLEANER ' A SOKMA [DAHA SONRA YAPILMASI DAHA DOĞRU OLABİLİR]
		while (lexer->tokens[i])
		{
			lexer->tokens[i] = cleaner(lexer->tokens[i], env);
			i++;
		}

		// PARSER İÇERİKLERİNİ EKRANA YAZDIRMA
		i = 0;
		t_parser *temp = parser;
		while (temp)
		{
			while (temp->cmds[i])
				printf("(%s) ", temp->cmds[i++]);
			i = 0;
			temp = temp->next;
			if (temp)
				printf("\n---pipe---\n");
		}
*/
