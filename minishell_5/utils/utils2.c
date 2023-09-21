#include "../minishell.h"

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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]); 
}

int	ft_iscontain(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}