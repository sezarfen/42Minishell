#include "../minishell.h"

char	**set_exec_args(t_parser *parser)
{
	char	**args;
	int		len;
	int		i;

	i = 0;
	len = split_len(parser->cmds);
	args = malloc(sizeof(char *) * (len + 1));
	while (parser->cmds[i])
	{
		args[i] = parser->cmds[i]; // no need to allocate memory for that
		i++;
	}
	args[i] = NULL;
	return (args); // args will be as {"ls", ... or NULL}
}

void	execute_fork(t_parser *parser, char **env)
{
	int		pid;
	char	**args;

	args = set_exec_args(parser);
	pid = fork();
	if (pid == 0)
	{
		execve(parser->cmds[0], args, env);
		printf("minishell: command not found: %s\n", parser->cmds[0]);
	}
	else
		wait(&pid);
}

void	execute_builtin(t_parser *parser)
{
	if (!ft_strncmp(parser->cmds[0], "cd", ft_strlen(parser->cmds[0])))
		cd(1, parser->cmds[1]);
}

void	to_execute(t_parser *parser, char **env)
{
	int	fd;

	while (parser)
	{
		if (parser->is_builtin)
			execute_builtin(parser);
		else
			execute_fork(parser, env);
		parser = parser->next;
	}
}
