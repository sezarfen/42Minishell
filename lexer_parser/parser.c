/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:47:10 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/05 16:08:49 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_parser(t_parser *parser, t_env *env)
{
	int	i;

	i = 0;
	while (parser)
	{
		if (ft_iscontain(parser->cmds[0], '$'))
			parser->dollar_command = 1;
		while (parser->cmds[i])
		{
			parser->cmds[i] = cleaner(parser->cmds[i], env, 0, 0);
			i++;
		}
		parser->is_builtin = is_builtin(parser->cmds[0]);
		i = 0;
		parser = parser->next;
	}
}

// ... < , > ...  extract from node
void	fill_parser(t_parser *parser, t_env *env, int i, int a)
{
	t_parser	*temp;

	temp = parser;
	while (parser)
	{
		while (parser->cmds[i])
		{
			if (is_output_redirect(parser->cmds[i]))
				output_redirect(parser, i);
			else if (is_input_redirect(parser->cmds[i]))
				input_redirect(parser, i);
			else if (is_heredoc(parser->cmds[i]))
				set_heredoc(parser, i, a);
			else if (is_append(parser->cmds[i]))
				open_in_append(parser, i);
			i++;
		}
		i = 0;
		parser = parser->next;
		a++;
	}
	redirect_cleaner(temp, 0, 0);
	clean_and_set_exec(temp, env);
	check_dollar_command(temp, env);
}

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

t_parser	*set_parser(t_lexer *lexer, int i, int k)
{
	t_parser	*parser;
	t_parser	*temp;
	int			len;

	parser = ft_calloc(sizeof(t_parser), 1);
	temp = parser;
	len = split_len(lexer->tokens);
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
