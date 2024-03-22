/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:23:35 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 11:23:35 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special(char *str)
{
	if (ft_strncmp(str, "|", 1) == 0)
		return (1);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (2);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(str, "<", 1) == 0)
		return (1);
	if (ft_strncmp(str, ">", 1) == 0)
		return (1);
	return (0);
}

int	is_pipe(char *str)
{
	if (!ft_strncmp(str, "|", ft_strlen(str)))
		return (1);
	return (0);
}

int	is_output_redirect(char *str)
{
	if (!ft_strncmp(str, ">", ft_strlen(str)))
		return (1);
	return (0);
}

int	is_input_redirect(char *str)
{
	if (!ft_strncmp(str, "<", ft_strlen(str)))
		return (1);
	return (0);
}

int	is_heredoc(char *str)
{
	if (!ft_strncmp(str, "<<", ft_strlen(str)))
		return (1);
	return (0);
}
