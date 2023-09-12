#include "../minishell.h"

int main()
{
	while (1)
	{
			char **lexer =	ft_split(readline("minishell$> "), ' ');

			if (!ft_strncmp(lexer[0], "pwd", 3))
				pwd();
			else if (!ft_strncmp(lexer[0], "cd", 3))
				cd(split_len(lexer) - 1, lexer[1]);
			else
				printf("minishell: %s: command not found\n", lexer[0]);
	}
	return (0);
}