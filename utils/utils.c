/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:24:30 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 14:24:30 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	equal_len(char *str)
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

void	free_split(char **split)
{
	int	i;

	i = split_len(split) - 1;
	while (i >= 0)
		free(split[i--]);
	free(split);
}
