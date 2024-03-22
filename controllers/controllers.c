/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:23:48 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/05 14:09:56 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	case_one(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (1);
	else if (!ft_strncmp(str, "<<", 2))
		return (1);
	else if (!ft_strncmp(str, ">", 1))
		return (1);
	else if (!ft_strncmp(str, "<", 1))
		return (1);
	return (0);
}

int	check_next(char *str)
{
	if (is_special(str) || str[0] == '\0')
		return (1);
	return (0);
}

int	lexer_control(t_lexer *lexer, int i)
{
	while (lexer->tokens[++i])
	{
		if (!ft_strncmp(lexer->tokens[i], "|", 1)
			&& check_next(lexer->tokens[i + 1]))
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			free_lexer(lexer);
			return (1);
		}
		else if (case_one(lexer->tokens[i]) && check_next(lexer->tokens[i + 1]))
		{
			if (is_input_redirect(lexer->tokens[i])
				&& access(lexer->tokens[i + 1], R_OK) == -1)
			{
				printf("minishell: %s"
					": No such file or directory\n", lexer->tokens[1]);
				free_lexer(lexer);
				return (1);
			}
			printf("minishell: syntax error near unexpected token `newline'\n");
			free_lexer(lexer);
			return (1);
		}
	}
	return (0);
}
