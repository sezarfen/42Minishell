#include "../minishell.h"

/*

(echo) (hello) (>) (a.txt) (-e) (|) (b.txt) (<) (wc) (-l)

>>>>>
	(echo) (hello) (-e) (|) (wc) (-l)
	stdin:	  0			 |		b.txt
	stdout:   a.txt  	 |      1 (could be handled later)
*/


void	output_cleaner(t_parser *parser) // probably have leaks :/
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (parser) // input_redirect için eksik var
	{
		while (parser->cmds[i])
		{
			if (is_output_redirect(parser->cmds[i]))
				i += 2;
			if (parser->cmds[i])
				parser->cmds[k++] = ft_strdup_impr(parser->cmds[i++]);
		}
		parser->cmds[k] = NULL;
		i = 0;
		k = 0;
		parser = parser->next;
	}
}

// Çok şükür Yarabbi
void	input_cleaner(t_parser *parser) // probably have leaks :/
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (parser) // input_redirect
	{
		while (parser->cmds[i])
		{
			if (is_input_redirect(parser->cmds[i])) // (echo)
			{
				k--;
				i++;
			}
			if (parser->cmds[i])
				parser->cmds[k++] = ft_strdup_impr(parser->cmds[i++]);
		}
		parser->cmds[k] = NULL;
		i = 0;
		k = 0;
		parser = parser->next;
	}
}
