#include "minishell.h"

int	split_len(char **split)	
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int		equal_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	return (i); 
}

// "Sa$USER" -> Safdundar
// 'Sa$USER' -> Safdundar
// Sa$USER   -> Safdundar

/*
int	find_env(char *str)
{
	if (ft_strncmp(str, "USER"))
}



char	*correct_words(char	*str)
{
	char	*new;
	int		i;
	int		k;

	new = malloc(sizeof(char) * ft_strlen(str) + 1);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			k = ++i;
			while (str[i] != '"' && str[i])  // "asd $USER 123"
			{
				if (str[i] == '$')
				{
					if (find_env(str + i))
					{

					}
				}
			}
				
			new = ft_strjoin(new, ft_substr(str, k, i - k));
		}
		i++;
	}
	return (new);
}

int main(int ac, char **av, char **env)
{
	char *new = correct_words(readline("minishell$ "));
	printf("%s\n", new);
	return (0); 
}
*/