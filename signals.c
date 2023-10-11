/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:24:04 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/08 11:24:04 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	default_sigint(int sig)
{
	if (g_exitstatus == 1453)
	{
		g_exitstatus = 2023;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		return ;
	}
	(void)sig;
	g_exitstatus = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	default_sigquit(int sig)
{
	(void)sig;
	printf("\b\b  \b\b");
}
