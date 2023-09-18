#include "../minishell.h"

int		case_one(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (1);
	else if (!ft_strncmp(str, "<<", 2))
		return (1);
	else if (!ft_strncmp(str, ">", 1))
		return (1);
	return (0);
}

int check_next(char *str)
{
	if (is_special(str) || str[0] == '\0')
		return (1);
	return (0);
}

int	lexer_control(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer->tokens[i])
	{
		if (!ft_strncmp(lexer->tokens[i], "|", 1) && check_next(lexer->tokens[i + 1]))
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return 1;
		}
		else if (case_one(lexer->tokens[i]) && check_next(lexer->tokens[i + 1]))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return 1;
		}
		else if (!ft_strncmp(lexer->tokens[i], "<", 1) && (i - 1 < 0 || check_next(lexer->tokens[i + 1])))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return 1;
		}
		i++;
	}
	return (0);
}
