/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:40:12 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 11:40:12 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_fork(t_parser *parser, char **env)
{
	char	**args;

	args = set_exec_args(parser);
	dup_redirections(parser);
	execve(parser->cmds[0], args, env);
	printf("minishell: command not found: %s\n", parser->cmds[0]);
	exit(127);
}

void	wait_and_set_status(t_env **penv, t_parser *parser, int *pids)
{
	int		exit_status;
	char	*status;
	int		len;
	int		i;

	i = 0;
	len = parser_len(parser);
	while (i < len)
	{
		waitpid(pids[i], &exit_status, 0);
		i++;
	}
	free(pids);
	close_files(parser);
	status = ft_itoa(WEXITSTATUS(exit_status));
	add_to_env(&(*penv), "?", status);
	free(status);
}

int	*set_fds(t_parser *parser)
{
	int	len;
	int	*fds;
	int	fd[2];
	int	i;
	int	k;

	len = parser_len(parser);
	fds = malloc(sizeof(int) * ((len - 1) * 2));
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

// waiting for change
void	to_execute(t_parser *parser, char **env, t_ee **ee)
{
	int			fd_in;
	int			fd[2];
	pid_t		pid;
	t_parser	*temp;
	int			*pids;
	int			i;

	fd_in = 0;
	i = 0;
	pids = malloc(sizeof(int) * (parser_len(parser)));
	while (parser)
	{
		pipe(fd);
		pid = fork();
		pids[i] = pid;
		if (pid == 0)
		{
			dup2(fd_in, 0);
			if (parser->next)
				dup2(fd[1], 1);
			close(fd[0]);
			if (parser->is_builtin || ft_iscontain(parser->cmds[0], '='))
				child_builtins(parser, ee);
			else
				execute_fork(parser, env);
			exit(0);
		}
		if (i > 0)
			close(fd_in);
		if (!parser->next)
			temp = parser;
		fd_in = fd[0];
		close(fd[1]);
		execute_builtin(parser, ee);
		parser = parser->next;
		i++;
	}
	if (fd_in)
		close(fd_in);
	wait_and_set_status(&((*ee)->env), temp, pids);
}
