#include "../minishell.h"



// echo hello > a.txt | b.txt < cat -e
// (echo) (hello) (>) (a.txt) (|) (b.txt) (<) (cat) (-e)

void	collect_tokens(t_parser *parser, int k, int i, t_lexer *lexer)
{
	int	len;
	int	a;

	len = i - k;
	a = 0;
	parser->cmds = ft_calloc(sizeof(char *), (len + 1));
	while (k < i)
		parser->cmds[a++] = ft_strdup(lexer->tokens[k++]);
}

t_parser	*set_parser(t_lexer *lexer)
{
	t_parser	*parser;
	t_parser	*temp;
	int			len;
	int			i;
	int			k;

	parser = ft_calloc(sizeof(t_parser), 1);
	temp = parser;
	len = split_len(lexer->tokens);
	i = 0;
	k = 0;
	while (i < len)
	{
		if (is_pipe(lexer->tokens[i]))
		{
			collect_tokens(temp, k, i, lexer);
			temp->next = ft_calloc(sizeof(t_parser), 1);
			temp = temp->next;
			k = i + 1;
		}
		else if (!lexer->tokens[i + 1])
			collect_tokens(temp, k, i + 1, lexer);
		i++;
	}
	temp->next = NULL;
	return (parser);
}
