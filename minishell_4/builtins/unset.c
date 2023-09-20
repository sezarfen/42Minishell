#include "../minishell.h"

void	unset(char *element, t_env **env)
{
	t_env	*temp;
	int		len;
	int		i;
	int		k;

	len = split_len((*env)->key);
	temp = malloc(sizeof(t_env));
	temp->key = ft_calloc(sizeof(char *), len + 1);
	temp->value = ft_calloc(sizeof(char *), len + 1);
	i = 0;
	k = 0;
	while ((*env)->key[i])
	{
		if (ft_strncmp(element, (*env)->key[i], ft_strlen(element)))
		{
			temp->key[k] = ft_strdup((*env)->key[i]);
			temp->value[k++] = ft_strdup((*env)->value[i]);
		}
		i++;
	}
	free_env((*env));
	(*env) = temp;
}
