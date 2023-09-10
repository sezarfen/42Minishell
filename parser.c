#include "minishell.h"

int	is_builtin(char *str) // each integer will represent different builtin function
{
	if (!ft_strncmp(str, "echo", 4))
		return (1);
	else if (!ft_strncmp(str, "cd", 2))
		return (2);
	else if (!ft_strncmp(str, "pwd", 3))
		return (3);
	else if (!ft_strncmp(str, "export", 2))
		return (4);
	else if (!ft_strncmp(str, "unset", 4))
		return (5);
	else if (!ft_strncmp(str, "env", 3))
		return (6);
	else if (!ft_strncmp(str, "exit", 4))
		return (7);
	return (0);
}

int	open_file(char	*file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR | O_CREAT);
	return (fd);
}

t_parser	*set_parser(t_lexer *lexer)
{
	t_parser	*parser;
	t_parser	*temp;
	int			i;
	int			j;
	int			k;
	int			len = split_len(lexer->tokens);

	parser = malloc(sizeof(t_parser));
	temp = parser;
	i = 0;
	j = 0;
	k = 0;
	while (i < len + 1)
	{
		if (!lexer->tokens[i])
		{
			temp->cmds = ft_calloc(sizeof(char *), (i - k + 1));
			temp->is_builtin = is_builtin(lexer->tokens[k]);
			temp->fd_in = 0;
			temp->fd_out = 0;
			while (lexer->tokens[k])
			{
				if (ft_strncmp(lexer->tokens[k], ">", 1) == 0)
				{
					temp->fd_out = open_file(lexer->tokens[k + 1]);
					k++;
				}
				else if (lexer->tokens[k + 1])
				{
					if (ft_strncmp(lexer->tokens[k + 1], "<", 1) == 0)
					{
						temp->fd_in = open_file(lexer->tokens[k]);
						k++;
					}
				}
				else
					temp->cmds[j++] = ft_substr(lexer->tokens[k], 0, ft_strlen(lexer->tokens[k]));
				k++;
			}
			j = 0;
			temp->next = NULL;
			break;
		}
		else if (ft_strncmp(lexer->tokens[i], "|", 1) == 0)
		{
			temp->cmds = ft_calloc(sizeof(char *), (i - k + 1));
			i = k;
			temp->is_builtin = is_builtin(lexer->tokens[i]);
			temp->fd_in = 0;
			temp->fd_out = 0;
			while (ft_strncmp(lexer->tokens[i], "|", 1))
			{
				if (ft_strncmp(lexer->tokens[i], ">", 1) == 0)
				{
					temp->fd_out = open_file(lexer->tokens[i + 1]);
					i++;
				}
				else if (lexer->tokens[i + 1])
				{
					if (ft_strncmp(lexer->tokens[i + 1], "<", 1) == 0)
					{
						temp->fd_in = open_file(lexer->tokens[i]);
						i++;
					}
				}
				else
					temp->cmds[j++] = ft_substr(lexer->tokens[i], 0, ft_strlen(lexer->tokens[i]));
				i++;
			}
			j = 0;
			temp->next = malloc(sizeof(t_parser));
			temp = temp->next;
			k = i + 1;
		}
		i++;
	}
	i = 0;
	while (parser)
	{
		while (parser->cmds[i])
			printf("%s\n", parser->cmds[i++]);
		printf("stdin:   %d\n", parser->fd_in);
		printf("stdout:  %d\n", parser->fd_out);
		printf("builtin: %d\n", parser->is_builtin);
		i = 0;
		parser = parser->next;
		if (parser)
			printf("=======FOUND PIPE=======\n");
	}
	return (parser);
}
