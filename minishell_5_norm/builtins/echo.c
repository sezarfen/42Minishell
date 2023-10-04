/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:01:16 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 11:01:16 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(t_parser *parser)
{
	int	i;
	int	f;

	i = 1;
	f = 0;
	if (!ft_strcmp(parser->cmds[i], "-n"))
	{
		i++;
		f++;
	}
	if (parser->cmds[1] == NULL)
		printf("\n");
	while (parser->cmds[i])
	{
		if (parser->cmds[i + 1])
			printf("%s ", parser->cmds[i]);
		else if (!parser->cmds[i + 1] && f == 0)
			printf("%s\n", parser->cmds[i]);
		else if (!parser->cmds[i + 1] && f == 1)
			printf("%s", parser->cmds[i]);
		i++;
	}
}
