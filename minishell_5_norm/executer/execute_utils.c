/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:40:48 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 11:40:48 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_penv(char *str, t_env **penv)
{
	char	*key;
	char	*value;

	key = ft_substr(str, 0, equal_len(str));
	value = ft_substr(str, equal_len(str) + 1, ft_strlen(str));
	add_to_env(&(*penv), key, value);
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
		args[i] = parser->cmds[i];
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	dup_redirections(t_parser *parser)
{
	if (parser->fd_in != 0 || parser->hd_in != 0)
		dup2(get_max(parser->hd_in, parser->fd_in), STDIN_FILENO);
	if (parser->fd_out != 0)
		dup2(parser->fd_out, STDOUT_FILENO);
}

// for parent process
void	close_files(t_parser *parser)
{
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

// closing file for 1 child process
void	close_file(t_parser *parser)
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
