#include "../minishell.h"


void	cd(int argc, char *args, t_ee **ee) // main process ' de çalıştırmak lazım
{
	char	cwd[256];
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
		getcwd(cwd, 256);
		add_to_env(&((*ee)->env), "OLDPWD", cwd);
		if (chdir(args) == -1)
			printf("bash: cd: %s: No such file or directory\n", args);
		getcwd(cwd, 256);
		add_to_env(&((*ee)->env), "PWD", cwd);
	}
}
