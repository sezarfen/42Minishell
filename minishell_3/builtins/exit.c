#include "../minishell.h"

void	exit_builtin(t_parser *parser)
{
	int	exit_code;
	int	len;

	exit_code = 0;
	len = split_len(parser->cmds);
	if (len > 2)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	if (len == 2)
		exit_code = ft_atoi(parser->cmds[1]);
	exit(exit_code);
}