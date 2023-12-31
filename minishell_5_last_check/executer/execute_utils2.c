/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:42:48 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 11:42:48 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_builtins(t_parser *parser, t_ee **ee)
{
	dup_redirections(parser);
	if (!ft_strcmp(parser->cmds[0], "echo"))
		echo(parser);
	else if (!ft_strcmp(parser->cmds[0], "pwd"))
		pwd();
	else if (!ft_strcmp(parser->cmds[0], "env"))
		env_builtin((*ee)->env);
}

void	execute_builtin(t_parser *parser, t_ee **ee)
{
	if (ft_iscontain(parser->cmds[0], '='))
		add_to_penv(parser->cmds[0], &((*ee)->penv));
	else if (!ft_strcmp(parser->cmds[0], "cd"))
		cd(split_len(parser->cmds) - 1, parser->cmds[1], ee);
	else if (!ft_strcmp(parser->cmds[0], "exit"))
		exit_builtin(parser);
	else if (!ft_strcmp(parser->cmds[0], "unset"))
		unset(parser->cmds[1], &((*ee)->env));
	else if (!ft_strcmp(parser->cmds[0], "export"))
		export(parser->cmds + 1, &((*ee)->env), &((*ee)->penv), -1);
}

void	set_pipe(int fd[], int i, int len)
{
	if (i % 2 == 0 && len > 1)
		dup2(fd[1], STDOUT_FILENO);
	else if (i % 2 == 1 && len == 2)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	add_to_penv(char *str, t_env **penv)
{
	char	*key;
	char	*value;

	key = ft_substr(str, 0, equal_len(str));
	value = ft_substr(str, equal_len(str) + 1, ft_strlen(str));
	add_to_env(&(*penv), key, value);
}
