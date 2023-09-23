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
