#include "../minishell.h"

/*

(echo) (hello) (>) (a.txt) (-e) (|) (b.txt) (<) (wc) (-l)

>>>>>
	(echo) (hello) (-e) (|) (wc) (-l)
	stdin:	  0			 |		b.txt
	stdout:   a.txt  	 |      1 (could be handled later)
*/


void	redirect_cleaner(t_parser *parser, int i, int k) // probably have leaks :/
{
	while (parser)
	{
		while (parser->cmds[i])
		{
			if (is_output_redirect(parser->cmds[i]) || is_append(parser->cmds[i])
				|| is_input_redirect(parser->cmds[i]))
			{
				free(parser->cmds[i++]); // this could solve the leak problem
				free(parser->cmds[i++]);
			}
			else if (is_heredoc(parser->cmds[i]))
			{
				free(parser->cmds[i++]);
				free(parser->cmds[i++]);
			}	
			if (parser->cmds[i] && !is_output_redirect(parser->cmds[i]) 
					&& !is_append(parser->cmds[i]) && !is_heredoc(parser->cmds[i])) // > a.txt > b.txt gibi durumlarda yardımcı oluyor (son 2 case)
				parser->cmds[k++] = ft_strdup_impr(parser->cmds[i++]);
		}
		parser->cmds[k] = NULL;
		i = 0;
		k = 0;
		parser = parser->next;
	}
}

// Çok şükür Yarabbi
void	input_cleaner(t_parser *parser, int i, int k) // probably have leaks :/
{
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
