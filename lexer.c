#include "minishell.h"

// echo "hello"world | wc -l <<a | cat '-e'
/*
(echo) ("hello"world) (|) (wc) (-l) (<<) (a) (|) (cat) ('-e')
*/
void	dq_helper(char *str, int *i)
{
    (*i)++;
    while (str[(*i)] != '"' && str[(*i)])
        (*i)++;
    if (str[(*i)] == '"')
        (*i)++;
    if (str[(*i)] != ' ' && str[(*i)])
    {
        while (str[(*i)] != ' ' && str[(*i)])
        (*i)++;
    }
}

void	sq_helper(char *str, int *i)
{
    (*i)++;
    while (str[(*i)] != '\'' && str[(*i)])
        (*i)++;
    if (str[(*i)] == '\'')
        (*i)++;
    if (str[(*i)] != ' ' && str[(*i)])
    {
        while (str[(*i)] != ' ' && str[(*i)])
        (*i)++;
    }
}


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
		if (str[i] == '\'' && str[i++]) // str[i] kısmına ulaşırsa bir ilerlesin diye
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

char	**the_lexer(char *str)
{
	char	**lexer;
	int		i;
	int		k;
	int		f;
	int		wc;

	count_quotes(str, 0, 0, 0);
	lexer = malloc(sizeof(char *) * (lexer_wc(str) + 1));  // lexer_wc nin değişmesi lazım
	i = 0;
	k = 0;
	f = 0;
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
				if (str[i] == '"')
					f++;
				while (f == 1)
				{
					i++;
					if (str[i] == '"')
						f--;
				}
				if (str[i] == '\'')
					f++;
				while (f == 1)
				{
					i++;
					if (str[i] == '\'')
						f--;
				}
				if (is_special(str + i)) // a><a gibi bir case sorun çıkarıyordu // altta if (... && !is_special )
				{
					if (str[i - 1] != ' ' && str[i - 1] && !is_special(str + i - 1))
					{
						lexer[wc] = malloc(sizeof(char) * (i - k + 1));
						ft_strlcpy(lexer[wc++], str + k, i - k + 1);
					}
					k = i;
					i += is_special(str + i);
					lexer[wc] = malloc(sizeof(char) * (i - k + 1));
					ft_strlcpy(lexer[wc++], str + k, i - k + 1);
					while (str[i] == ' ' && str[i++]); // if there is any ' ' it will pass
					k = i;
					if (is_special(str + i))
						i--;
				}
				i++;
			}
			lexer[wc] = malloc(sizeof(char) * (i - k + 1));
			ft_strlcpy(lexer[wc++], str + k, i - k + 1);
		}
	}
	lexer[wc] = NULL;
	return (lexer);
}

int main(int ac, char **av)
{
	int		i = 0;
	char	*str = readline("minishell$ ");
	printf("kelime sayisi -> %d\n", lexer_wc(str));
	char **lexer = the_lexer(str);
	printf("tokens:\n");
	while (lexer[i])
		printf("%s\n", lexer[i++]); 
	return (0);
}
