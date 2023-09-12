#include "../minishell.h"

int	is_special(char *str)
{
	if (ft_strncmp(str, "|", 1) == 0)
		return (1);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (2);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	return (0);
}

int	is_pipe(char *str)
{
	if (!ft_strncmp(str, "|", ft_strlen(str)))
		return (1);
	return (0);
}

int	is_output_redirect(char *str)
{
	if (!ft_strncmp(str, ">", ft_strlen(str)))
		return (1);
	return (0);
}

int	is_input_redirect(char *str)
{
	if (!ft_strncmp(str, "<", ft_strlen(str)))
		return (1);
	return (0);
}

int	is_heredoc(char *str)
{
	if (!ft_strncmp(str, "<<", ft_strlen(str)))
		return (1);
	return (0);
}
