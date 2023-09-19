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

void	dup_redirections(t_parser *parser)
{
	if (parser->fd_in != 0 || parser->hd_in != 0)
		dup2(get_max(parser->hd_in, parser->fd_in), STDIN_FILENO); // hangisi sonra açılmışsa o gelmiş daha büyük olacaktır
	if (parser->fd_out != 0)
		dup2(parser->fd_out, STDOUT_FILENO);
}

void	execute_fork(t_parser *parser, char **env)
{
	char	**args;

	args = set_exec_args(parser);
	dup_redirections(parser);
	execve(parser->cmds[0], args, env);
	printf("minishell: command not found: %s\n", parser->cmds[0]);
	exit(127);
}

void	child_builtins(t_parser *parser) // commands that will be executed in child process
{
	dup_redirections(parser);
	if (!ft_strncmp(parser->cmds[0], "echo", ft_strlen(parser->cmds[0])))
		echo(parser);
}

void	execute_builtin(t_parser *parser, t_env *env)
{
	if (!ft_strncmp(parser->cmds[0], "cd", ft_strlen(parser->cmds[0]))) // bu coniditonlar için özel bir fonksiyon yazılabilir
		cd(1, parser->cmds[1]);
	else if (!ft_strncmp(parser->cmds[0], "pwd", ft_strlen(parser->cmds[0])))
		pwd();
	else if (!ft_strncmp(parser->cmds[0], "env", ft_strlen(parser->cmds[0])))
		env_builtin(env);
	else if (!ft_strncmp(parser->cmds[0], "exit", ft_strlen(parser->cmds[0])))
		exit_builtin(parser);
}

void	set_pipe(int fd[], int i, int len) // need to be improved
{
	if (i % 2 == 0 && len > 1)
		dup2(fd[1], STDOUT_FILENO);
	else if (i % 2 == 1 && len == 2)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	to_execute(t_parser *parser, char **env, t_env *tenv) // parser_len iş yapacaktır, fork ve pipe sayısını belirtir
{
	int	len;
	int	i;
	int	fd[2];
	int	pid;

	len = parser_len(parser);
	pipe(fd);
	i = 0;
	while (parser)
	{
		pid = fork();
		if (pid == 0) // indicates child process
		{
			set_pipe(fd, i, len);
			if (parser->is_builtin)
				child_builtins(parser);
			else
				execute_fork(parser, env);
			exit(0);
		}
		else
			execute_builtin(parser, tenv);
		parser = parser->next;
		i++;
		if (i % 2 == 0 || i == len)
		{
			close(fd[1]);
			close(fd[0]);
		}
		waitpid(pid, NULL, 0);
	}
}
