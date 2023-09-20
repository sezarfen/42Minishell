#include "../minishell.h"

void	print_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		printf("%s\n", split[i++]);
}

int	get_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

char	*set_propmt(char *cwd)
{
	char	*prompt;

	prompt = ft_strdup("\033[34m┌─(\033[0m\033[31m");
	prompt = ft_strjoin(prompt, cwd, 1);
	prompt = ft_strjoin(prompt, "\033[0m\033[34m)"
	"───(\033[0m\033[31mhcivici & fdundar\033[0m\033[34m)\n"
	"└(\033[0m\033[1m\033[33mminishell\033[0m\033[34m)$>\033[0m ", 1);
	return (prompt);
}

int	parser_len(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser)
	{
		i++;
		parser = parser->next;
	}
	return (i);
}

int	ft_isfulldigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}