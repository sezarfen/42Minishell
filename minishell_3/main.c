#include "minishell.h"

t_lexer	*init_lexer(void)
{
	t_lexer	*tlexer;
	char	*str;
	char	*prompt;
	char 	cwd[256];

	getcwd(cwd, 256);
	prompt = set_propmt(cwd);
	str = readline(prompt);
	add_history(str);
	tlexer = malloc(sizeof(t_lexer));
	tlexer->tokens = the_lexer(str, 0, 0, 0);
	tlexer->size = split_len(tlexer->tokens);
	free(str);
	free(prompt);
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

t_env_exp	*set_env_exp(char **the_env)
{
	t_env_exp	*env_exp;

	env_exp = malloc(sizeof(t_env_exp));
	env_exp->env = set_env(the_env);
	env_exp->exp = set_env(the_env);
	return (env_exp);
}

int main(int ac, char **av, char **the_env)
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_env_exp	*env_exp;

	env_exp = set_env_exp(the_env);
	while (1)
	{
		lexer = init_lexer();
		if (lexer->tokens[0] == NULL || lexer_control(lexer))
			continue ;
		parser = set_parser(lexer, 0, 0);
		fill_parser(parser, env_exp->env);
		to_execute(parser, the_env, env_exp->env);
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

		// PRINT THE CLEANED PARSER
		printf("\n=========CLEANED PARSER=========\n");
		t_parser	*temp;
		int			i;
		temp = parser;
		i = 0;
		while (temp)
		{
			while (temp->cmds[i])
			{
				temp->cmds[i] = cleaner(temp->cmds[i], env_list);
				printf("%s ", temp->cmds[i++]);
			}
			i = 0;
			printf("\n");
			temp = temp->next;
			if (temp)
				printf("\n|==(pipe found)==|\n");
		}

		// DIFFERENT PARSER PRINT (WITH ATTRIBUTES)

		int i = 0;
		t_parser *temp = parser;
		while (temp)
		{
			while (temp->cmds[i])
				printf("(%s) ", temp->cmds[i++]);
			printf("\n");
			printf("fd_in:%d\nfd_out:%d\nis_builtin:%d\nhd_in:%d\n", temp->fd_in , temp->fd_out, temp->is_builtin, temp->hd_in);
			i = 0;
			temp = temp->next;
			if (temp)
				printf("\n---pipe---\n");
		}

/////////////////////////////////////////
	/*
		int i = 0;
		t_parser *temp = parser;
		while (temp)
		{
			while (temp->cmds[i])
				printf("(%s) ", temp->cmds[i++]);
			printf("\n");
			printf("fd_in:%d\nfd_out:%d\nis_builtin:%d\nhd_in:%d\n", temp->fd_in , temp->fd_out, temp->is_builtin, temp->hd_in);
			i = 0;
			temp = temp->next;
			if (temp)
				printf("\n---pipe---\n");
		}
	*/
//////////////////////////////////////////