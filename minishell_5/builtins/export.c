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

void	export(char **cmds, t_env **env, t_env **penv, int i) // asd=123 demeden asd denirse eklemesin // şu an (null) yapıyor
{
	if (cmds[0] == NULL)
	{
		print_exp(*penv);
		return ;
	}
	if (get_value_by_key(cmds[0], *penv))
		add_to_env(&(*env), cmds[0], get_value_by_key(cmds[0], *penv));
	while (cmds[++i])
	{
		if (ft_iscontain(cmds[i], '='))
		{
			add_to_env(&(*env), ft_substr(cmds[i], 0, equal_len(cmds[i])),
				ft_substr(cmds[i], equal_len(cmds[i]) + 1, ft_strlen(cmds[i]))); // leak yapabilir
			add_to_env(&(*penv), ft_substr(cmds[i], 0, equal_len(cmds[i])),
				ft_substr(cmds[i], equal_len(cmds[i]) + 1, ft_strlen(cmds[i]))); // leak yapabilir
		}
		else
			add_to_env(&(*penv), cmds[i], "");
	}
}


/*

void	export(char *str, t_env **env, t_env *penv) // asd=123 demeden asd denirse eklemesin // şu an (null) yapıyor
{													
	t_env	*temp;								
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
	if (get_value_by_key(str, penv)) // bu kısım vesilesyile asd set edilmeden export asd dersek eklemiyor
	{
		temp->key[i] = ft_substr(str, 0, equal_len(str));
		temp->value[i] = get_value_by_key(str, penv);
	}
	free_env((*env));
	(*env) = temp;
}

*/


