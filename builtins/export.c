/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:01:24 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 11:01:24 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	export(char **cmds, t_env **env, t_env **penv, int i)
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
				ft_substr(cmds[i], equal_len(cmds[i]) + 1, ft_strlen(cmds[i])));
			add_to_env(&(*penv), ft_substr(cmds[i], 0, equal_len(cmds[i])),
				ft_substr(cmds[i], equal_len(cmds[i]) + 1, ft_strlen(cmds[i])));
		}
		else
			add_to_env(&(*penv), cmds[i], "");
	}
}
