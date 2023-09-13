#include "../minishell.h"

// export (değişken ismi) // bash, değişken ismi varsa ekliyor, yoksa hiçbir şey yapmıyor

void	free_env(t_env *exp)
{
	int	i;

	i = 0;
	while (exp->key[i])
		free(exp->key[i++]);
	free(exp->key);
	i = 0;
	while (exp->value[i])
		free(exp->value[i++]);
	free(exp->value);
	free(exp);
}

t_env	*export(char *str, t_env *env, t_env *exp) // deneme amaçlıdır
{													// sanırım export içerisine de ekliyor
	t_env	*temp;									// bilen birine sor
	int		len;
	int		i;

	len = split_len(env->key);
	if (str == NULL)
	{
		print_env(exp);
		return (env);
	}
	temp = malloc(sizeof(t_env));
	temp->key = ft_calloc(sizeof(char *), (len + 2));
	temp->value = ft_calloc(sizeof(char *), (len + 2));
	i = 0;
	while (env->key[i])
	{
		temp->key[i] = ft_strdup(env->key[i]);
		temp->value[i] = ft_strdup(env->value[i]);
		i++;
	}
	temp->key[i] = ft_substr(str, 0, equal_len(str));
	temp->value[i] = ft_substr(str, equal_len(str) + 1, ft_strlen(str));
	free_env(env);
	return (temp);
}