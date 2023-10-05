#include "minishell.h"

void handle_it(int sig)
{
	printf("we got %d, and that means SIGPIPE\n", sig);
}
int main()
{
	int fd[2];

	pipe(fd);

	signal(SIGPIPE, handle_it);

	close(fd[0]);
	if (write(fd[1], "hello world\n", 12) == -1)
		printf("we got an error\n");

	return (0);
}