/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:53:53 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/09 21:53:53 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_ctrl_d(char *str, char *prompt)
{
	if (!str)
	{
		free(prompt);
		write(1, "\033[D\033[D", 7);
		printf("exit\n");
		exit(1);
	}
}

void	set_ints(int ints[3], int i, int k, int f)
{
	ints[0] = i;
	ints[1] = k;
	ints[2] = f;
}
