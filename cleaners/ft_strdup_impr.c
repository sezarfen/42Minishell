/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_impr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:23:05 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 11:23:05 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_impr(const char *s1)
{
	size_t	i;
	char	*dup;

	dup = malloc(ft_strlen(s1) + 1);
	if (!dup)
		return (0);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	free((void *)s1);
	return (dup);
}

char	*ft_strjoin_df(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1 || !s2)
		return (0);
	join = malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (0);
	i = 0;
	j = 0;
	while (s1[j])
		join[i++] = s1[j++];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	free((void *)s1);
	free((void *)s2);
	return (join);
}
