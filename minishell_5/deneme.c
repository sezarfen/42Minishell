#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int ac, char **av, char **env) // ./a.out(0) env(1) |(2) grep(3) USER(4)
{
	char *str = "/usr/bin/env";
	char *str2 = "/usr/bin/grep";
	char	*args1[] = {"env", 0};
	char	*args2[] = {"grep", "USER", 0};
	int fd[2];
	pid_t	pid;
	int	i;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(str, args1, env);
		exit(0);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execve(str2, args2, env);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}