/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:01:22 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 11:01:22 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// exit den bir önce t_ee freelebilir
void	exit_builtin(t_parser *parser)
{
	int	exit_code;
	int	len;

	exit_code = 0;
	len = split_len(parser->cmds);
	if (len > 2)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	if (len == 2)
	{
		if (!ft_isfulldigit(parser->cmds[1]))
		{
			printf("minishell: exit:"
				" %s: numeric argument required\n",
				parser->cmds[1]);
			exit(2);
		}
		exit_code = ft_atoi(parser->cmds[1]);
	}
	free_parser(parser);
	exit(exit_code);
}
