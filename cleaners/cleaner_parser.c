/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:10:39 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 11:10:39 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_cleaner(t_parser *parser, int i, int k)
{
	while (parser)
	{
		while (parser->cmds[i])
		{
			if (is_redirects(parser->cmds[i]))
			{
				free(parser->cmds[i++]);
				free(parser->cmds[i++]);
			}
			else if (is_heredoc(parser->cmds[i]))
			{
				free(parser->cmds[i++]);
				free(parser->cmds[i++]);
			}
			if (parser->cmds[i] && !is_output_redirect(parser->cmds[i])
				&& !is_append(parser->cmds[i])
				&& !is_heredoc(parser->cmds[i]))
				parser->cmds[k++] = ft_strdup_impr(parser->cmds[i++]);
		}
		parser->cmds[k] = NULL;
		i = 0;
		k = 0;
		parser = parser->next;
	}
}

// Çok şükür Yarabbi
void	input_cleaner(t_parser *parser, int i, int k)
{
	while (parser)
	{
		while (parser->cmds[i])
		{
			if (is_input_redirect(parser->cmds[i]))
			{
				k--;
				i++;
			}
			if (parser->cmds[i])
				parser->cmds[k++] = ft_strdup_impr(parser->cmds[i++]);
		}
		parser->cmds[k] = NULL;
		i = 0;
		k = 0;
		parser = parser->next;
	}
}
