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

void	export(char *str, t_env **env, t_env *penv) // deneme amaçlıdır
{													// sanırım export içerisine de ekliyor
	t_env	*temp;									// bilen birine sor
	int		len;
	int		i;

	len = split_len((*env)->key);
	if (str == NULL)
	{
		print_exp((*env));
		return ;
	}
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
	// bu kısımda private_env den bul ve ekle diye bir şey yapılamlı
	temp->key[i] = ft_substr(str, 0, equal_len(str));
	temp->value[i] = get_value_by_key(str, penv);
	free_env((*env));
	(*env) = temp;
}
