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

int	is_env_contain(t_env *env, char *find)
{
	int	i;
	
	i = 0;
	while (env->key[i])
	{
		if (!ft_strncmp(env->key[i], find, ft_strlen(env->key[i])))
			return (1);
		i++;
	}
	return (0);
}

void	update_env(t_env **env, char *key, char *value)
{
	int	i;
	
	i = 0;
	while ((*env)->key[i])
	{
		if (!ft_strncmp((*env)->key[i], key, ft_strlen((*env)->key[i])))
		{
			free((*env)->value[i]);
			(*env)->value[i] = ft_strdup(value);
		}
		i++;
	}
}

void	add_to_env(t_env **env, char *key, char *value) // void could be change later
{  // eğer ? varsa onu update etsin yeni eklemesin
	t_env	*temp;
	int		len;
	int		i;

	if (is_env_contain((*env), key))
	{
		update_env(&(*env), key, value);
		return ;
	}
	len = split_len((*env)->key);
	temp = malloc(sizeof(t_env));
	temp->key = ft_calloc(sizeof(char *), (len + 2));
	temp->value = ft_calloc(sizeof(char *), (len + 2));
	i = 0;
	while ((*env)->key[i])
	{
		temp->key[i] = ft_strdup((*env)->key[i]);
		temp->value[i] = ft_strdup((*env)->value[i]);
		i++;
	}
	temp->key[i] = ft_strdup(key); 
	temp->value[i] = ft_strdup(value);
	free_env(*env);
	(*env) = temp;
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