#include "minishell.h"

// He"llo"World -> HelloWorld yapmasını istiyoruz
// suggested function -> ft_substr, ft_strjoin
/*

	eğer stringi dolaşırken " ya da ' ile karşılaşırsak
	bundan bir tane daha olmalı (kurallar onu gerektiriyor).
	Diğer eşini bulana kadar devam ederiz, " içerisindeysek
	$ ile başlayan değişken var mı yok mu bunu kontrol etmemiz gerekecektir
*/

// null probleminin önüne geçmek için hep ft_strjoin(clean, ft_substr(...)); kullanılabilir

/* NORMINETTE ' YE UYMASI İÇİN NESTED FONSKİYONLAR İLERİDE KULLANIRIZ

void	nest_one(char **clean, char *str, int *i, int *k)
{
	*clean = ft_strjoin(*clean, ft_substr(str, *k, *i - *k));
	*k = ++(*i);
	while (str[*i] != '"' && str[*i])
		(*i)++;
	*clean = ft_strjoin(*clean, ft_substr(str, *k, *i - *k));
	(*k) = (*i) + 1;
}
*/

char	*find_in_env(char *str, int *i)
{
	int	n;
	
	n = 0;
	while (str[n] != ' ' && str[n] != '"' && str[n] != '\'')
		n++;
	*i += n;
	if (!ft_strncmp(str + 1, "USER", n - 1))
		return (ft_strdup("fdundar"));
	if (!ft_strncmp(str + 1, "PATH", n - 1))
		return (ft_strdup("/mnt/c/Users/TR/Desktop/minishell"));
	return (ft_strdup(""));
}

char	*cleaner(char *str)
{
	char	*clean;
	int		len;
	int		i;
	int		k;

	i = 0;
	k = 0; // set this variable as a start point of substr
	len = ft_strlen(str);
	clean = ft_strdup("");
	while (i <= len)
	{
		if (str[i] == '"')
		{
			clean = ft_strjoin(clean, ft_substr(str, k, i - k));
			k = ++i;
			while (str[i] != '"' && str[i])
			{
				if (str[i] == '$')
				{
					clean = ft_strjoin(clean, ft_substr(str, k, i - k));
					clean = ft_strjoin(clean, find_in_env(str + i, &i));
					k = i + (str[i] == '"'); // hi norminette
				}
				i++;
			}
			clean = ft_strjoin(clean, ft_substr(str, k, i - k));
			k = i + 1;
		}
		else if (str[i] == '\'')
		{
			clean = ft_strjoin(clean, ft_substr(str, k, i - k));
			k = ++i;
			while (str[i] != '\'' && str[i])
			{
				i++;
			}
			clean = ft_strjoin(clean, ft_substr(str, k, i - k)); // 'asd'123 "asd $USER qwe" asd
			k = i + 1;
		}
		else if (!str[i] && str[i - 1] != '"' && str[i - 1] != '\'') // which indicates end of the string, without " or '.
			clean = ft_strjoin(clean, ft_substr(str, k, i - k));
		else if (str[i] == '$')
		{
			clean = ft_strjoin(clean, ft_substr(str, k, i - k));
			clean = ft_strjoin(clean, find_in_env(str + i, &i));
			k = i + (str[i] == '"'); // hi norminette
		}
		i++;
	}
	return (clean);
}

/*
int main(void)
{
	char *clean = cleaner(readline("deneme$ "));
	printf("%s\n", clean);
	return (0);
}
*/