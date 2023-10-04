/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:59:54 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 10:59:54 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(int argc, char *args, t_ee **ee)
{
	char	cwd[256];

	if (argc > 1)
	{
		printf("minishell: cd: too many arguments\n");
		return ;
	}
	if (argc == 0)
	{
		chdir("/mnt");
		chdir("..");
	}
	else
	{
		getcwd(cwd, 256);
		add_to_env(&((*ee)->env), "OLDPWD", cwd);
		if (chdir(args) == -1)
			printf("bash: cd: %s: No such file or directory\n", args);
		getcwd(cwd, 256);
		add_to_env(&((*ee)->env), "PWD", cwd);
	}
}
