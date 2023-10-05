/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:24:36 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 14:24:36 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 2 blocks leak buradaymış :) Çok Şükür Halloldu [line 27]
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
		free(parser->cmds);
		i = 0;
		parser = parser->next;
	}
	while (temp)
	{
		parser = temp->next;
		free(temp);
		temp = parser;
	}
}

void	free_ee(t_ee *ee)
{
	free_env(ee->env);
	free_env(ee->penv);
	free(ee);
}

char	*get_value_by_key(char *key, t_env *env)
{
	int	i;

	i = 0;
	while (env->key[i])
	{
		if (!ft_strncmp(env->key[i], key, ft_strlen(key)))
			return (env->value[i]);
		i++;
	}
	return (NULL);
}

void	check_av(char **av)
{
	printf("minishell: %s: No such file or directory\n", av[1]);
	exit(0);
}
