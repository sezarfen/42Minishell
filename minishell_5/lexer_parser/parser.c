#include "../minishell.h"

void	set_heredoc(t_parser *parser, int i) 
{	// gizli bir dosya açıp içine yazıp onu << ile değiştirebiliriz
	int		fd;
	char	*str;
	char	*eof;

	fd = open(".heredoc.txt", O_CREAT | O_RDWR | O_APPEND , 0777); // DOSYAYI OKUYAMIYORUM?
	eof = parser->cmds[i + 1];
	while (1)
	{
		str = readline(" >");
		if (!ft_strncmp(str, eof, ft_strlen(str)))
		{
			free(str);
			close(fd);
			break ;
		}
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
		free(str);
	}
	parser->hd_in = fd;
}

void	clean_parser(t_parser *parser, t_env *env) // gonna set is_builtin here otherwise, it can't understand something like "ec"'ho'
{
	int	i;

	i = 0;
	while (parser)
	{
		while (parser->cmds[i])
		{
			parser->cmds[i] = cleaner(parser->cmds[i], env);
			i++;
		}
		parser->is_builtin = is_builtin(parser->cmds[0]);
		i = 0;
		parser = parser->next;
	}
}

void	fill_parser(t_parser *parser, t_env *env) // ... < , > ...  gibi kısımları node'dan çıkaralım 
{
	t_parser	*temp; // temp ve i fonksiyona parametre olarak verilebilir
	int			i;

	i = 0;
	temp = parser;
	while (parser)
	{
		while (parser->cmds[i]) // buraya bir append ve heredoc da eklenebilir
		{
			if (is_output_redirect(parser->cmds[i]))
				output_redirect(parser, i); // (echo)
			else if (is_input_redirect(parser->cmds[i]))
				input_redirect(parser, i);
			else if (is_heredoc(parser->cmds[i]))
				set_heredoc(parser, i);
			else if (is_append(parser->cmds[i]))
				open_in_append(parser, i);
			i++;
		}
		i = 0;
		parser = parser->next;
	}
	redirect_cleaner(temp, 0, 0); // (echo)
	//input_cleaner(temp, 0, 0);
	clean_and_set_exec(temp, env); // cleani bu kısmın içerisinde yapıyorum
}

void	collect_tokens(t_parser *parser, int k, int i, t_lexer *lexer)
{
	int	len;
	int	a;

	len = i - k;
	a = 0;
	parser->cmds = ft_calloc(sizeof(char *), (len + 1));
	while (k < i)
		parser->cmds[a++] = ft_strdup(lexer->tokens[k++]);
} // normal dup kullanarak yapıyor, zaten ileride free_lexer kullancağız

t_parser	*set_parser(t_lexer *lexer, int i, int k)
{
	t_parser	*parser;
	t_parser	*temp;
	int			len;

	parser = ft_calloc(sizeof(t_parser), 1);
	temp = parser;
	len = split_len(lexer->tokens);
	while (i < len)
	{
		if (is_pipe(lexer->tokens[i]))
		{
			collect_tokens(temp, k, i, lexer);
			temp->next = ft_calloc(sizeof(t_parser), 1);
			temp = temp->next;
			k = i + 1;
		}
		else if (!lexer->tokens[i + 1])
			collect_tokens(temp, k, i + 1, lexer);
		i++;
	}
	temp->next = NULL;
	return (parser);
}
