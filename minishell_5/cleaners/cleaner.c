#include "../minishell.h"

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

char	*find_in_env(char *str, int *i, t_env *env) // $ işaretinin başından geliyor $USER gibi
{
	int	n;
	int	j;

	n = 0; // "$USER"  // $USER$USER problemli
	while (str[n] != ' ' && str[n] != '"' && str[n] != '\'' && str[n]) // "$US'" gibi bir case ' de durduruyor ama zaten US' diye bir değişken yok, özellikle bir şey denemek isteyenler için handle edilebilir
		n++;
	*i += n;
	j = 0;
	while (env->key[j])
	{		// str + 1, "$USER  ASDAS G" gibi olabileceğinden ft_strcmp kullanılmadı
		if (!ft_strncmp(str + 1, env->key[j], get_max(n - 1, ft_strlen(env->key[j]))))
			return (ft_strdup(env->value[j]));
		j++;
	}
	if (n == 1)
		return (ft_strdup("$"));
	return (ft_strdup(""));
}

char	*cleaner(char *str, t_env *env) // echo $USER'$USER' gibi bir case'de hata var
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
			clean = ft_strjoin_df(clean, ft_substr(str, k, i - k));
			k = ++i;
			while (str[i] != '"' && str[i]) // "$USER"'$USER' case'i sıkıntılı
			{								// sebebi single quote parsing olabilir, tekrar bakılabilir
				if (str[i] == '$')
				{
					clean = ft_strjoin_df(clean, ft_substr(str, k, i - k));
					clean = ft_strjoin_df(clean, find_in_env(str + i, &i, env));
					k = i + (str[i] == '"'); // hi norminette
				}
				i++;
			}
			clean = ft_strjoin_df(clean,  ft_substr(str, k, i - k));
			k = i + 1;
		}
		else if (str[i] == '\'')
		{
			clean = ft_strjoin_df(clean, ft_substr(str, k, i - k));
			k = ++i;
			while (str[i] != '\'' && str[i])
				i++;
			clean = ft_strjoin_df(clean, ft_substr(str, k, i - k)); // 'asd'123 "asd $USER qwe" asd
			k = i + 1;
		}
		else if (!str[i] && str[i - 1] != '"' && str[i - 1] != '\'') // which indicates end of the string, without " or '.
			clean = ft_strjoin_df(clean, ft_substr(str, k, i - k));
		else if (str[i] == '$') // $USER
		{
			clean = ft_strjoin_df(clean, ft_substr(str, k, i - k));
			clean = ft_strjoin_df(clean, find_in_env(str + i, &i, env));
			k = i + (str[i] == '"'); // hi norminette
		}
		i++;
	}
	free(str);
	return (clean);
}
/*
char	*cleaner(char *str, t_env *env) // echo $USER'$USER' gibi bir case'de hata var
{
	char	*clean;
	int		len;
	int		i;
	int		k;
	char	*temp; // ft_strjoin() ' len boş olarak kullanılıyordu, onlar için freelemek için kullanıldı

	i = 0;
	k = 0; // set this variable as a start point of substr
	len = ft_strlen(str);
	clean = ft_strdup("");
	while (i <= len)
	{
		if (str[i] == '"')
		{
			temp = ft_substr(str, k, i - k);
			clean = ft_strjoin(clean, temp, 1);
			free(temp);
			k = ++i;
			while (str[i] != '"' && str[i]) // "$USER"'$USER' case'i sıkıntılı
			{								// sebebi single quote parsing olabilir, tekrar bakılabilir
				if (str[i] == '$')
				{
					temp = ft_substr(str, k, i - k);
					clean = ft_strjoin(clean, temp, 1);
					free(temp);
					temp = find_in_env(str + i, &i, env);
					clean = ft_strjoin(clean, temp, 1);
					free(temp);
					k = i + (str[i] == '"'); // hi norminette
				}
				i++;
			}
			temp = ft_substr(str, k, i - k);
			clean = ft_strjoin(clean, temp, 1);
			free(temp);
			k = i + 1;
		}
		else if (str[i] == '\'')
		{
			temp = ft_substr(str, k, i - k);
			clean = ft_strjoin(clean, temp, 1);
			free(temp);
			k = ++i;
			while (str[i] != '\'' && str[i])
				i++;
			temp = ft_substr(str, k, i - k);
			clean = ft_strjoin(clean, temp, 1); // 'asd'123 "asd $USER qwe" asd
			free(temp);
			k = i + 1;
		}
		else if (!str[i] && str[i - 1] != '"' && str[i - 1] != '\'') // which indicates end of the string, without " or '.
		{
			temp = ft_substr(str, k, i - k);
			clean = ft_strjoin(clean, temp, 1);
			free(temp);
		}	
		else if (str[i] == '$') // $USER
		{
			temp = ft_substr(str, k, i - k);
			clean = ft_strjoin(clean, temp, 1);
			free(temp);
			temp = find_in_env(str + i, &i, env);
			clean = ft_strjoin(clean, temp, 1);
			free(temp);
			k = i + (str[i] == '"'); // hi norminette
		}
		i++;
	}
	free(str);
	return (clean);
}
*/

/*
int main(void)
{
	char *clean = cleaner(readline("deneme$ "));
	printf("%s\n", clean);
	return (0);
}
*/