#include "minishell.h"

void	set_exec(t_parser *parser) // munmap_chunk(): invalid pointer // hatası alınabiliyor
{
	char	*path;
	char	**paths;
	char	*command;
	int		i;

	path = getenv("PATH"); // do not free that returned value
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i] && !parser->is_builtin)
	{
		command = ft_strjoin(paths[i], "/", 0);
		command = ft_strjoin(command, parser->cmds[0], 1);
		printf("path searched -> %s\n", command);
		if (!access(command, X_OK))
		{
			free(parser->cmds[0]);
			parser->cmds[0] = ft_strdup_impr(command);
			command = NULL;
		}
		free(command);
		i++;
	}
	free_split(paths);
}

void	set_right_exec(t_parser *parser)
{
	while (parser)
	{
		set_exec(parser);
		parser = parser->next;
	}
}
