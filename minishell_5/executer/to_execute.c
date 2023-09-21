#include "../minishell.h"

void	add_to_penv(char *str, t_env **penv)
{
	char	*key;
	char	*value;

	key = ft_substr(str, 0, equal_len(str));
	value = ft_substr(str, equal_len(str) + 1, ft_strlen(str));
	add_to_env(&(*penv), key, value); // updates or generates
}

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
	if (!ft_strcmp(parser->cmds[0], "echo"))
		echo(parser);
}

void	execute_builtin(t_parser *parser, t_ee **ee) // main process'deki çıktılarda pipe'dan geçirilmeli
{
	if (ft_iscontain(parser->cmds[0], '='))
		add_to_penv(parser->cmds[0], &((*ee)->penv)); // add to export gibi bir şey yazabiliriz
	else if(!ft_strcmp(parser->cmds[0], "cd")) 
		cd(1, parser->cmds[1]);
	else if (!ft_strcmp(parser->cmds[0], "pwd"))
		pwd();
	else if (!ft_strcmp(parser->cmds[0], "env"))
		env_builtin((*ee)->env);
	else if (!ft_strcmp(parser->cmds[0], "exit"))
		exit_builtin(parser);
	else if (!ft_strcmp(parser->cmds[0], "unset"))
		unset(parser->cmds[1], &((*ee)->env));
	else if (!ft_strcmp(parser->cmds[0], "export"))
		export(parser->cmds + 1, &((*ee)->env), &((*ee)->penv), -1);
	////  is_contain_equal diye bir şey yapalım (başa eklemek lazım, env=3 gibi bir şey gelirse ona girsin)
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

void	wait_and_set_status(pid_t pid, t_env **penv,t_parser *parser)
{
	int		exit_status;
	char	*status;

	waitpid(pid, &exit_status, 0);
	if (parser->next == NULL)
	{
		status = ft_itoa(WEXITSTATUS(exit_status));
		add_to_env(&(*penv), "?", status); // program açılır açılmaz set edilmiş olmuyor
		free(status); // '?' ' de penv içerisinde set edilse daha doğru olur 
	}					// ama $? araması sırasında problem oluşturabilir
}

void	to_execute(t_parser *parser, char **env, t_ee **ee) // parser_len iş yapacaktır, fork ve pipe sayısını belirtir
{
	int		fd_in;
	int		fd[2];
	pid_t	pid;

	fd_in = 0;
	while (parser)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd_in, 0); // set input to previous one // it is 0 at the beginning
			if (parser->next)
				dup2(fd[1], 1); // set output if there is pipe
			close(fd[0]);
			// command execute part
			if (parser->is_builtin || ft_iscontain(parser->cmds[0], '='))
				child_builtins(parser);
			else
				execute_fork(parser, env);
			exit(0);
		}
		else
		{
			wait_and_set_status(pid, &((*ee)->env), parser);
			close(fd[1]);
			fd_in = fd[0]; //save the input for the next command
			execute_builtin(parser, ee);
			parser = parser->next;
		}
	}
}


/*

// OLD EXECUTE // ONLY WORKS FOR 2 PIPES
void	to_execute(t_parser *parser, char **env, t_ee **ee) // parser_len iş yapacaktır, fork ve pipe sayısını belirtir
{
	int		len;
	int		i;
	int		fd[2];
	pid_t	pid;

	len = parser_len(parser);
	pipe(fd);
	i = 0;
	while (parser)
	{
		pid = fork();
		if (pid == 0) // indicates child process
		{
			set_pipe(fd, i, len);
			if (parser->is_builtin || ft_iscontain(parser->cmds[0], '='))
				child_builtins(parser);
			else
				execute_fork(parser, env);
			exit(0);
		}
		else
			execute_builtin(parser, &(*ee));




		parser = parser->next;
		i++;
		if (i % 2 == 0 || i == len)
		{
			close(fd[1]);
			close(fd[0]);
		}
		wait_and_set_status(pid, &((*ee)->env), i, len);
	}
}

*/