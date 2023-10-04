/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:23:37 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 11:23:37 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	else if (!ft_strcmp(str, "echo"))
		return (2);
	else if (!ft_strcmp(str, "cd"))
		return (3);
	else if (!ft_strcmp(str, "pwd"))
		return (4);
	else if (!ft_strcmp(str, "export"))
		return (5);
	else if (!ft_strcmp(str, "unset"))
		return (6);
	else if (!ft_strcmp(str, "env"))
		return (7);
	else if (!ft_strcmp(str, "exit"))
		return (8);
	return (0);
}

int	is_append(char *str)
{
	if (!ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

int	is_redirects(char *str)
{
	if (is_output_redirect(str)
		|| is_append(str)
		|| is_input_redirect(str)
		return (1);
	return (0);
}
