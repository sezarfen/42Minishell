#include "minishell.h"

void	handle_signal(int signal)
{
	if (signal == SIGQUIT) // 2 geri git 2 boşluk yaz 2 geri git
	{
		write(1, "\e[13", 1);
	}
	else if (signal == SIGINT)
	{
		write(1, "\e[13", 1);
	}
}

void	check_av(char **av)
{
	printf("minishell: %s: No such file or directory\n", av[1]);
	exit(0);
}

t_lexer	*init_lexer(void)
{
	t_lexer	*tlexer;
	char	*str;
	char	*prompt;

	prompt = set_propmt();
	str = readline(prompt);
	if (!str) // CTRL + D is given at beginning
	{
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
		env->value[i] = ft_substr(the_env[i], equal_len(the_env[i]) + 1, ft_strlen(the_env[i]));
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
	env_exp->env = set_env(the_env, 1); // ?=0 "$?" kullanmak için (f == 1)
	env_exp->penv = set_env(the_env, 0);
	return (env_exp);
}

int main(int ac, char **av, char **the_env)
{
	t_lexer		*lexer; // (echo) ("hello"world'hi') (|) ("w"c)
	t_parser	*parser; // 2 nodes will be generated -> (.. untill pipe)[node 1] (after pipe..)[node 2]
 	t_ee		*env_exp; 

	if (ac == 2)
		check_av(av);
	env_exp = set_env_exp(the_env);
	// SIGNAL HANDLE İŞLEMLERİNİ SOR
	//signal(SIGQUIT, handle_signal);
	//signal(SIGINT, handle_signal);
	while (1)
	{
		lexer = init_lexer(); // checked for leaks
		if (lexer->tokens[0] == NULL || lexer_control(lexer))
			continue ;
		parser = set_parser(lexer, 0, 0);
		fill_parser(parser, env_exp->env);
		free_lexer(lexer);
		to_execute(parser, the_env, &env_exp);
		free_parser(parser);
		free_ee(env_exp);
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
*/
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