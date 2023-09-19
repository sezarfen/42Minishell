#include "../minishell.h"

void	pwd(void)
{
	char	buff[256];

	getcwd(buff, 256);
	printf("%s\n", buff);
}