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

int	open_again(char *hd_name)
{
	int	fd;

	fd = open(hd_name, O_RDWR);
	if (fd == -1)
		printf("An error occured!\n");
	return (fd);
}

void	dup_redirections(t_parser *parser)
{
	if (parser->hd_in > 0)
		parser->hd_in = open_again(parser->hd_name);
	if (parser->fd_in != 0 || parser->hd_in != 0)
		dup2(get_max(parser->hd_in, parser->fd_in), STDIN_FILENO);
	if (parser->fd_out != 0)
		dup2(parser->fd_out, STDOUT_FILENO);
}

// for parent process
void	close_files(t_parser *parser)
{
	while (parser)
	{
		while (parser->fd_num >= 0)
		{
			if (parser->fds[parser->fd_num] > 2)
				close(parser->fds[parser->fd_num]);
			parser->fd_num--;
		}
		if (parser->hd_in)
			close(parser->hd_in);
		parser = parser->next;
	}
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
