#include "../minishell.h"

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	else if (!ft_strcmp(str, "echo"))
		return (2);
	else if (!ft_strcmp(str, "cd"))
		return (3);
	else if (!ft_strcmp(str, "pwd"))
		return (4);
	else if (!ft_strcmp(str, "export"))
		return (5);
	else if (!ft_strcmp(str, "unset"))
		return (6);
	else if (!ft_strcmp(str, "env"))
		return (7);
	else if (!ft_strcmp(str, "exit"))
		return (8);
	return (0); // indicates, it is not a buildin function
}

int	is_append(char *str)
{
	if (!ft_strcmp(str, ">>"))
		return (1);
	return (0);
}
