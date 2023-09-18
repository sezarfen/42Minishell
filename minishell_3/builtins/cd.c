#include "../minishell.h"


void	cd(int argc, char *args) // main process ' de çalıştırmak lazım
{
	if (argc > 1)
	{
		printf("minishell: cd: too many arguments\n");
		return ;
	}
	if (argc == 0)
	{
		chdir("/mnt"); // XD case dediklerimizden
		chdir("..");
	}
	else // if argc == 1
	{
		if (chdir(args) == -1)
			printf("bash: cd: %s: No such file or directory\n", args);
	}
}
