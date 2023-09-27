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

void	child_builtins(t_parser *parser, t_ee **ee) // commands that will be executed in child process
{
	dup_redirections(parser);
	if (!ft_strcmp(parser->cmds[0], "echo"))
		echo(parser);
	else if (!ft_strcmp(parser->cmds[0], "pwd"))
		pwd();
	else if (!ft_strcmp(parser->cmds[0], "env"))
		env_builtin((*ee)->env);
}

void	execute_builtin(t_parser *parser, t_ee **ee) // main process'deki çıktılarda pipe'dan geçirilmeli
{
	if (ft_iscontain(parser->cmds[0], '='))
		add_to_penv(parser->cmds[0], &((*ee)->penv)); // add to export gibi bir şey yazabiliriz
	else if(!ft_strcmp(parser->cmds[0], "cd")) 
		cd(1, parser->cmds[1], ee);
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

void	wait_and_set_status(pid_t pid, t_env **penv ,t_parser *parser)
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

int	*set_fds(t_parser *parser)
{
	int	len;
	int	*fds;
	int	fd[2];
	int	i;
	int	k;

	len = parser_len(parser);
	fds = malloc(sizeof(int) * ((len - 1) * 2)); // 1 pipe -> 2 parser node -> 1 pipe
	i = 0;
	k = 0;
	while (i < (len - 1) * 2)
	{
		pipe(fd);
		fds[i++] = fd[k++];
		fds[i++] = fd[k++];
		k = 0;
	}
	return (fds);
}

void	close_files(t_parser *parser) // for parent process
{ // search parsers, find max fd, close it untill 2 starting from max fd
	int	max_fd;

	max_fd = 0;
	while (parser)
	{
		if (parser->fd_in > max_fd)
			max_fd = parser->fd_in;
		if (parser->fd_out > max_fd)
			max_fd = parser->fd_out;
		if (parser->hd_in > max_fd)
			max_fd = parser->hd_in;
		parser = parser->next;
	}
	while (max_fd >= 3)
		close(max_fd--);
}

void	close_file(t_parser *parser) // closing file for 1 child process
{
	int	max_fd;

	max_fd = 0;
	if (parser->fd_in > max_fd)
		max_fd = parser->fd_in;
	if (parser->fd_out > max_fd)
		max_fd = parser->fd_out;
	if (parser->hd_in > max_fd)
		max_fd = parser->hd_in;
	while (max_fd >= 3)
		close(max_fd--);
}

void	to_execute(t_parser *parser, char **env, t_ee **ee) // parser_len iş yapacaktır, fork ve pipe sayısını belirtir
{
	int		fd_in;
	int		fd[2];
	pid_t	pid;
	t_parser	*temp;
	t_parser	*first;

	fd_in = 0;
	first = parser;
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
			if (parser->is_builtin || ft_iscontain(parser->cmds[0], '='))
				child_builtins(parser, ee);
			else
				execute_fork(parser, env);
			close_file(parser);
			exit(0);
		}
		if (!parser->next) // indicates last node
			temp = parser;
		fd_in = fd[0];
		close(fd[1]);
		execute_builtin(parser, ee);
		parser = parser->next;
	}
	wait_and_set_status(pid, &((*ee)->env), temp);
	close_files(first);
}

/*
void	to_execute(t_parser *parser, char **env, t_ee **ee) // parser_len iş yapacaktır, fork ve pipe sayısını belirtir
{
	int		fd_in;
	int		fd[2];
	pid_t	pid;
	t_parser	*temp;

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
			if (parser->is_builtin || ft_iscontain(parser->cmds[0], '='))
				child_builtins(parser, ee);
			else
				execute_fork(parser, env);
			exit(0);
		}
		if (!parser->next) // indicates last node
			temp = parser;
		fd_in = fd[0];
		close(fd[1]);
		execute_builtin(parser, ee);
		parser = parser->next;
	}
	wait_and_set_status(pid, &((*ee)->env), temp);
}
*/
/*
void	to_execute(t_parser *parser, char **env, t_ee **ee)
{
	int		*fds;
	pid_t	pid;
	int		i;
	int		fd_temp;

	fds = set_fds(parser); // will close them at the end
	i = 1;
	fd_temp = 0;
	while (parser)
	{
		pid = fork();
		if (pid == 0)
		{	// stdin filenos -> 1 3 5 7.. // stdout filenos -> 0 2 4 6..
			dup2(fd_temp, STDIN_FILENO); 
			if (parser->next)
				dup2(fds[i + 1], STDOUT_FILENO);
			if (parser->is_builtin || ft_iscontain(parser->cmds[0], '='))
				child_builtins(parser, ee);
			else
				execute_fork(parser, env);
			exit(0);
		}
		fd_temp = fds[i];
		execute_builtin(parser, ee);
		i += 2;
		parser = parser->next;
	}
	wait_and_set_status(pid, &((*ee)->penv), parser);
	while (i >= 0)
		close(fds[i--]);
}
*/

/*
void	to_execute(t_parser *parser, char **env, t_ee **ee) // parser_len iş yapacaktır, fork ve pipe sayısını belirtir
{
	int		fd_in;
	int		fd[2];
	pid_t	pid;
	t_parser	*temp;

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
			if (parser->is_builtin || ft_iscontain(parser->cmds[0], '='))
				child_builtins(parser, ee);
			else
				execute_fork(parser, env);
			exit(0);
		}
		if (!parser->next) // indicates last node
			temp = parser;
		fd_in = fd[0];
		close(fd[1]);
		execute_builtin(parser, ee);
		parser = parser->next;
	}
	wait_and_set_status(pid, &((*ee)->env), temp);
}
*/

/*
void	to_execute(t_parser *parser, char **env, t_ee **ee) // parser_len iş yapacaktır, fork ve pipe sayısını belirtir
{
	int		i;
	int		len;
	pid_t	pid;
	int		temp_fd;

	len = parser_len(parser); // will indicate number of commands will be executed
	int fd[len][2];
	i = 0;
	temp_fd = 0;
	while (i < len)
		pipe(fd[i]);
	i = 0;
	while (parser)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(temp_fd, STDIN_FILENO);
			if (parser->next)
				dup2(fd[i][1], STDOUT_FILENO);
			close(fd[i][0]);
			///		EXECUTE PART	///
			if (parser->is_builtin || ft_iscontain(parser->cmds[0], '='))
				child_builtins(parser, ee);
			else
				execute_fork(parser, env);
			exit(0);
		}
		temp_fd = fd[i][0];
		close(fd[i][1]);
		execute_builtin(parser, ee);
		parser = parser->next;
		i++;
	}
	i = 0;
	while (i < len)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	wait_and_set_status(pid, &((*ee)->env), parser);
}
*/


/*  LAST TO_EXECUTE COMMAND
void	to_execute(t_parser *parser, char **env, t_ee **ee) // parser_len iş yapacaktır, fork ve pipe sayısını belirtir
{
	int		fd_in;
	int		fd[2];
	pid_t	pid;
	t_parser	*temp;

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
			if (parser->is_builtin || ft_iscontain(parser->cmds[0], '='))
				child_builtins(parser, ee);
			else
				execute_fork(parser, env);
			exit(0);
		}
		if (!parser->next) // indicates last node
			temp = parser;
		fd_in = fd[0];
		close(fd[1]);
		execute_builtin(parser, ee);
		parser = parser->next;
	}
	wait_and_set_status(pid, &((*ee)->env), temp);
}

*/

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
