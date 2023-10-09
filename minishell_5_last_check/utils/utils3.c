/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:24:34 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 14:24:34 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		printf("%s\n", split[i++]);
}

int	get_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

char	*set_propmt(void)
{
	char	*prompt;
	char	cwd[256];

	getcwd(cwd, 256);
	prompt = ft_strdup("");
	prompt = ft_strjoin(prompt, "(\033[31mhcivici & fdundar\033[0m)"
			"──(\033[0m\033[1m\033[33mminishell\033[0m)$> ", 1);
	return (prompt);
}

int	parser_len(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser)
	{
		i++;
		parser = parser->next;
	}
	return (i);
}

int	ft_isfulldigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
