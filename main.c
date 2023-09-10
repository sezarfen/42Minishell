#include "minishell.h"

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
	t_env		*env;

	env = set_env(the_env);
	lexer = init_lexer();
	int	i = 0;
	while (lexer->tokens[i])
	{
		lexer->tokens[i] = cleaner(lexer->tokens[i]);
		i++;
	}
	i = 0;
	while (lexer->tokens[i])
		printf("%s\n", lexer->tokens[i++]);
	//printf("\n----------PARSER----------\n");
	//parser = set_parser(lexer);
	return (0);
}
