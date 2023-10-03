#include "../minishell.h"

void	echo(t_parser *parser) // -n flagını daha eklemedik // (-n) sadece 2. parametre ise bakılıyor
{ 					// echoyu da child process ' de çalıştırıp, pipe ile kullanmalıyız
	int	i;
	int	f;

	i = 1;
	f = 0;
	if (!ft_strcmp(parser->cmds[i], "-n"))
	{
		i++;
		f++;
	}
	if (parser->cmds[1] == NULL) // bu yada split_len(parser->cmds) == 1 çalışmıyor nedense 
		printf("\n"); // -> sadece echo yazınca çalışmıyor
	while (parser->cmds[i])
	{
		if (parser->cmds[i + 1])
			printf("%s ", parser->cmds[i]);
		else if (!parser->cmds[i + 1] && f == 0)
			printf("%s\n", parser->cmds[i]);
		else if (!parser->cmds[i + 1] && f == 1)
			printf("%s", parser->cmds[i]);
		i++;
	}
}
