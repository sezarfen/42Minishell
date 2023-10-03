#include "../minishell.h"

void	free_lexer(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer->tokens[i])
	{
		free(lexer->tokens[i]);
		lexer->tokens[i] = NULL;
		i++;
	}
	free(lexer->tokens);
	free(lexer);
}

void	free_parser(t_parser *parser)
{
	t_parser	*temp;
	int			i;

	temp = parser;
	i = 0;
	while (parser)
	{
		while (parser->cmds[i])
			free(parser->cmds[i++]);
		i = 0;
		parser = parser->next;
	}
	while (temp)
	{
		free(temp);
		temp = temp->next;
	}
}

void	free_ee(t_ee *ee) // also uses rl_clear_history
{
	free_env(ee->env);
	free_env(ee->penv);
	free(ee);
}
