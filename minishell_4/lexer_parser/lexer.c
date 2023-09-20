#include "../minishell.h"

void	lexer_wc_inner(char *str, int *i, int *f)
{
	if (str[(*i)] == '"')
		(*f)++;
	while ((*f) == 1)
	{
		(*i)++;
		if (str[(*i)] == '"')
			(*f)--;
	}
	if (str[*i] == '\'')
		(*f)++;
	while ((*f) == 1)
	{
		(*i)++;
		if (str[(*i)] == '\'') 
			(*f)--;
	}
}


int        lexer_wc(char *str)
{
	int	i;
	int	f;
	int	wc;

	i = 0;
	f = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] != ' ' && str[i])
		{
			wc++;
			while (str[i] != ' ' && str[i])
			{
				lexer_wc_inner(str, &i, &f);
				if (is_special(str + i) && wc++ && wc++)
					i += is_special(str + i);
				i++;
			}
		}
	}
	return (wc);
}


void	count_quotes(char *str, int i, int j, int k)
{
	while (str[i])
	{
		if (str[i] == '\'' && str[i++])
		{
			j++;
			while (str[i] != '\'' && str[i++]);
			if (str[i] == '\'' && str[i++])
				j++;
		}
		else if (str[i] == '"' && str[i++])
		{
			k++;
			while (str[i] != '"' && str[i++]); 
			if (str[i] == '"' && str[i++])
				k++;
		}
		else
			i++;
	}
	if (j % 2 == 1 || k % 2 == 1)
	{
		printf("quotes count error\n");
		exit (1);
	}	
}

void	pass_quotes(char *str, int *i, int *f)
{
	if (str[*i] == '"')
		(*f)++;
	while (*f == 1)
	{
		(*i)++;
		if (str[*i] == '"')
			(*f)--;
	}
	if (str[*i] == '\'')
		(*f)++;
	while (*f == 1)
	{
		(*i)++;
		if (str[*i] == '\'')
			(*f)--;
	}
}

char	**the_lexer(char *str, int i, int k, int f)
{
	char	**lexer;
	int		wc;

	count_quotes(str, 0, 0, 0);
	lexer = malloc(sizeof(char *) * (lexer_wc(str) + 1));  // lexer_wc nin değişmesi lazım
	wc = 0;
	while (str[i])
	{
		while (str[i] == ' ' && str[i])	
			i++;
		if (str[i] != ' ' && str[i])
		{
			k = i;
			while (str[i] != ' ' && str[i])
			{
				pass_quotes(str, &i, &f);
				if (is_special(str + i)) // a><a gibi bir case sorun çıkarıyordu // altta if (... && !is_special )
				{
					if (str[i - 1] != ' ' && str[i - 1] && !is_special(str + i - 1))
						lexer[wc++] = ft_substr(str, k, i - k);
					k = i;
					i += is_special(str + i);
					lexer[wc++] = ft_substr(str, k, i - k);
					while (str[i] == ' ' && str[i++]); // if there is any ' ' it will pass
					k = i;
					if (is_special(str + i))
						i--;
					if ((str[i] == '\'' || str[i] == '"') && i--)
						NULL;
				}
				i++;
			}
			lexer[wc++] = ft_substr(str, k, i - k);
		}
	}
	lexer[wc] = NULL;
	return (lexer);
}

