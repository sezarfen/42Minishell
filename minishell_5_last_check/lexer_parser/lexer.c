/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:47:05 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/09 22:07:50 by fdundar          ###   ########.fr       */
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

void	need_func(int ints[3], char *str, char **lexer, int *wc)
{
	while (str[ints[0]] != ' ' && str[ints[0]])
	{
		pass_quotes(str, &ints[0], &ints[2]);
		if (is_special(str + ints[0]))
		{
			if (ints[0] && str[ints[0] - 1] != ' '
				&& str[ints[0] - 1]
				&& !is_special(str + ints[0] - 1))
				lexer[(*wc)++] = ft_substr(str, ints[1], ints[0] - ints[1]);
			ints[1] = ints[0];
			ints[0] += is_special(str + ints[0]);
			lexer[(*wc)++] = ft_substr(str, ints[1], ints[0] - ints[1]);
			lexer_nest_one(str, &ints[0], &ints[1]);
		}
		ints[0]++;
	}
}

// num[0] represents current index, num[1] is start point, num[2] is flag check
char	**the_lexer(char *str)
{
	char	**lexer;
	int		wc;
	int		ints[3];

	count_quotes(str, 0, 0, 0);
	set_ints(ints, 0, 0, 0);
	lexer = malloc(sizeof(char *) * (lexer_wc(str) + 1));
	wc = 0;
	while (str[ints[0]])
	{
		while (str[ints[0]] == ' ' || str[ints[0]] == '\t')
			ints[0]++;
		if (str[ints[0]] != ' ' && str[ints[0]])
		{
			ints[1] = ints[0];
			need_func(ints, str, lexer, &wc);
			lexer[wc++] = ft_substr(str, ints[1], ints[0] - ints[1]);
		}
	}
	lexer[wc] = NULL;
	return (lexer);
}
