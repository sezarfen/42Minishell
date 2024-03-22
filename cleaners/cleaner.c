/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:23:07 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 11:23:07 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_in_env(char *str, int *i, t_env *env)
{
	int	n;
	int	j;

	n = 1;
	while (str[n] != ' ' && str[n] != '"' && str[n] != '\''
		&& str[n] && str[n] != '$')
		n++;
	*i += n;
	j = 0;
	while (env->key[j])
	{
		if (!ft_strncmp(str + 1, env->key[j],
				get_max(n - 1, ft_strlen(env->key[j]))))
			return (ft_strdup(env->value[j]));
		j++;
	}
	if (n == 1)
		return (ft_strdup("$"));
	return (ft_strdup(""));
}

void	clean_in_env(char **clean, char **str, int *i, int *k)
{
	*clean = ft_strjoin_df(*clean, ft_substr(*str, *k, *i - *k));
	*k = ++(*i);
	while ((*str)[(*i)] != '\'')
		(*i)++;
	*clean = ft_strjoin_df(*clean, ft_substr(*str, *k, *i - *k));
	*k = ++(*i);
}

void	cleaner_conditions(char *str, char **clean, int *i, int *k)
{
	if (str[*i] == '\'')
		clean_in_env(&(*clean), &str, &(*i), &(*k));
	if (!str[*i])
		*clean = ft_strjoin_df(*clean, ft_substr(str, *k, *i - *k));
	if (str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
}

void	pass_double_quote(t_env *env, char *str, int *i, int *k)
{
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			env->clean = ft_strjoin_df(env->clean, ft_substr(str, *k, *i - *k));
			env->clean = ft_strjoin_df(env->clean,
					find_in_env(str + *i, &(*i), env));
			*k = *i;
		}
		if (str[*i] != '"' && str[*i] != '$')
			(*i)++;
	}
}

/*
// Çok şükür yarabbel alemin , İnşaAllah bu daha etkili olmuştur
 // env->clean added for this function
*/
char	*cleaner(char *str, t_env *env, int i, int k)
{
	int		len;

	len = ft_strlen(str);
	env->clean = ft_strdup("");
	while (i <= len)
	{
		if (str[i] == '"')
		{
			env->clean = ft_strjoin_df(env->clean, ft_substr(str, k, i - k));
			k = ++i;
			pass_double_quote(env, str, &i, &k);
			env->clean = ft_strjoin_df(env->clean, ft_substr(str, k, i - k));
			k = ++i;
		}
		if (str[i] == '$')
		{
			env->clean = ft_strjoin_df(env->clean, ft_substr(str, k, i - k));
			env->clean = ft_strjoin_df(env->clean,
					find_in_env(str + i, &i, env));
			k = i;
		}
		cleaner_conditions(str, &(env->clean), &i, &k);
	}
	free(str);
	return (env->clean);
}
