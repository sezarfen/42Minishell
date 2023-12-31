#include "../minishell.h"

void	expand_dollar(t_parser *parser, t_env *env)
{
	char		**temp_cmds;
	char		**dollar;
	int			i;
	int			k;

	i = 0;
	k = 0;
	temp_cmds = parser->cmds;
	dollar = ft_split(parser->cmds[0], ' ');
	parser->cmds = ft_calloc(sizeof(char *), split_len(dollar) + split_len(temp_cmds) + 1);
	while (dollar[k])
		parser->cmds[i++] = ft_strdup(dollar[k++]);
	k = 1; // k starts from 1 in order to not get $command
	while (temp_cmds[k])
		parser->cmds[i++] = ft_strdup(temp_cmds[k++]);
	set_exec(parser, env);
	free_split(temp_cmds);
	free_split(dollar);
}

void	check_dollar_command(t_parser *parser, t_env *env)
{
	while (parser)
	{
		if (parser->dollar_command)
			expand_dollar(parser, env);
		parser = parser->next;
	}
}

char	*set_filename(int a)
{
	char	*file_name;

	file_name = ft_strdup(".heredoc_");
	file_name = ft_strjoin_df(file_name, ft_itoa(a));
	file_name = ft_strjoin(file_name, ".txt", 1);
	return (file_name);
}

void	set_heredoc(t_parser *parser, int i, int a) 
{	// gizli bir dosya açıp içine yazıp onu << ile değiştirebiliriz
	int		fd;
	char	*str;
	char	*eof;
	char	*file_name;

	file_name = set_filename(a);
	fd = open(file_name, O_CREAT | O_RDWR | O_APPEND , 0777); // DOSYAYI OKUYAMIYORUM?
	free(file_name);
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
		if (ft_iscontain(parser->cmds[0], '$'))
			parser->dollar_command = 1;
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
	int			a;

	i = 0;
	temp = parser;
	a = 0;
	while (parser)
	{
		while (parser->cmds[i]) // buraya bir append ve heredoc da eklenebilir
		{
			if (is_output_redirect(parser->cmds[i]))
				output_redirect(parser, i); // (echo)
			else if (is_input_redirect(parser->cmds[i]))
				input_redirect(parser, i);
			else if (is_heredoc(parser->cmds[i]))
				set_heredoc(parser, i, a);
			else if (is_append(parser->cmds[i]))
				open_in_append(parser, i);
			i++;
		}
		i = 0;
		parser = parser->next;
		a++;
	}
	redirect_cleaner(temp, 0, 0); // (echo)
	clean_and_set_exec(temp, env); // cleani bu kısmın içerisinde yapıyorum
	check_dollar_command(temp, env);
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
