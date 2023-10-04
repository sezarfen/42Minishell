/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:47:05 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 14:22:21 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_wc_inner(char *str, int *i, int *f)
{
	if (str[(*i)] == '"')
		(*f)++;
	while ((*f) == 1)
	{
		(*i)++;
		if (str[(*i)] == '"')
			(*f)--;
	}
	if (str[*i] == '\'')
		(*f)++;
	while ((*f) == 1)
	{
		(*i)++;
		if (str[(*i)] == '\'')
			(*f)--;
	}
}

int	lexer_wc(char *str)
{
	int	i;
	int	f;
	int	wc;

	i = 0;
	f = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] != ' ' && str[i])
		{
			wc++;
			while (str[i] != ' ' && str[i])
			{
				lexer_wc_inner(str, &i, &f);
				if (is_special(str + i) && wc++ && wc++)
					i += is_special(str + i);
				i++;
			}
		}
	}
	return (wc);
}

void	pass_quotes(char *str, int *i, int *f)
{
	if (str[*i] == '"')
		(*f)++;
	while (*f == 1)
	{
		(*i)++;
		if (str[*i] == '"')
			(*f)--;
	}
	if (str[*i] == '\'')
		(*f)++;
	while (*f == 1)
	{
		(*i)++;
		if (str[*i] == '\'')
			(*f)--;
	}
}

void	lexer_nest_one(char *str, int *i, int *k)
{
	while (str[(*i)] == ' ' && str[(*i)])
		(*i)++;
	(*k) = (*i);
	if (is_special(str + (*i)))
		(*i)--;
	if ((str[(*i)] == '\'' || str[(*i)] == '"'))
		(*i)--;
}

char	**the_lexer(char *str, int i, int k, int f)
{
	char	**lexer;
	int		wc;

	count_quotes(str, 0, 0, 0);
	lexer = malloc(sizeof(char *) * (lexer_wc(str) + 1));
	wc = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] != ' ' && str[i])
		{
			k = i;
			while (str[i] != ' ' && str[i])
			{
				pass_quotes(str, &i, &f);
				if (is_special(str + i))
				{
					if (str[i - 1] != ' ' && str[i - 1] && !is_special(str + i - 1))
						lexer[wc++] = ft_substr(str, k, i - k);
					k = i;
					i += is_special(str + i);
					lexer[wc++] = ft_substr(str, k, i - k);
					lexer_nest_one(str, &i, &k);
				}
				i++;
			}
			lexer[wc++] = ft_substr(str, k, i - k);
		}
	}
	lexer[wc] = NULL;
	return (lexer);
}
