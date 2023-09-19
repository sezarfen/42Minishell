#include "../minishell.h"

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", ft_strlen(str)))
		return (1);
	else if (!ft_strncmp(str, "echo", ft_strlen(str)))
		return (2);
	else if (!ft_strncmp(str, "cd", ft_strlen(str)))
		return (3);
	else if (!ft_strncmp(str, "pwd", ft_strlen(str)))
		return (4);
	else if (!ft_strncmp(str, "export", ft_strlen(str)))
		return (5);
	else if (!ft_strncmp(str, "unset", ft_strlen(str)))
		return (6);
	else if (!ft_strncmp(str, "env", ft_strlen(str)))
		return (7);
	else if (!ft_strncmp(str, "exit", ft_strlen(str)))
		return (8);
	return (0); // indicates, it is not a buildin function
}

int	is_append(char *str)
{
	if (!ft_strncmp(str, ">>", ft_strlen(str)))
		return (1);
	return (0);
}
