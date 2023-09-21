#include "../minishell.h"

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

void	print_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->key[i])
	{
		printf("%s=%s\n", env->key[i], env->value[i]);
		i++;
	}
}

void	print_exp(t_env *penv)
{
	int	i;

	i = 0;
	while (penv->key[i])
	{
		if (penv->value[i][0] == '\0')
			printf("declare -x %s\n", penv->key[i]);
		else
			printf("declare -x %s=\"%s\"\n", penv->key[i], penv->value[i]);
		i++;
	}
}

char	*get_value_by_key(char *key, t_env *env)
{
	int	i;

	i = 0;
	while (env->key[i])
	{
		if (!ft_strncmp(env->key[i], key, ft_strlen(key)))
			return (env->value[i]);
		i++;
	}
	return (NULL);
}

void	free_split(char **split)
{
	int	i;

	i = split_len(split) - 1;
	while (i >= 0)
		free(split[i--]);
	free(split);
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

// char *args = 
// execve("ls", {"ls", "-l", "-a"}, env);