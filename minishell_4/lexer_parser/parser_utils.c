#include "../minishell.h"

void	output_redirect(t_parser *parser, int i)
{
	parser->fd_out = open(parser->cmds[i + 1], O_CREAT | O_RDWR, 0777);
	if (parser->fd_out == -1)
		printf("cannot open that file...");
}

void	input_redirect(t_parser *parser, int i)
{
	parser->fd_in = open(parser->cmds[i + 1], O_CREAT | O_RDWR, 0777);
	if (parser->fd_out == -1)
		printf("cannot open that file...");
}

void	open_in_append(t_parser *parser, int i)
{
	parser->fd_out = open(parser->cmds[i + 1], O_CREAT | O_RDWR | O_APPEND, 0777);
	if (parser->fd_out == -1)
		printf("cannot open that file...");
}
