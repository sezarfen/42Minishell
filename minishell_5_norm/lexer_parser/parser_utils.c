/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:47:08 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 14:09:16 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	output_redirect(t_parser *parser, int i)
{
	parser->fd_out = open(parser->cmds[i + 1], O_CREAT | O_RDWR, 0777);
	if (parser->fd_out == -1)
		printf("cannot open that file...");
}

void	input_redirect(t_parser *parser, int i)
{
	parser->fd_in = open(parser->cmds[i + 1], O_CREAT | O_RDWR, 0777);
	if (parser->fd_out == -1)
		printf("cannot open that file...");
}

void	open_in_append(t_parser *parser, int i)
{
	parser->fd_out = open(parser->cmds[i + 1], O_CREAT | O_RDWR | O_APPEND, 0777);
	if (parser->fd_out == -1)
		printf("cannot open that file...");
}

void	count_quotes(char *str, int i, int j, int k)
{
	while (str[i])
	{
		if (str[i] == '\'' && str[i++])
		{
			j++;
			while (str[i] != '\'' && str[i])
				i++;
			if (str[i] == '\'' && str[i++])
				j++;
		}
		else if (str[i] == '"' && str[i++])
		{
			k++;
			while (str[i] != '"' && str[i])
				i++;
			if (str[i] == '"' && str[i++])
				k++;
		}
		else
			i++;
	}
	if (j % 2 == 1 || k % 2 == 1 && printf("quotes count error\n"))
		exit (1);
}
