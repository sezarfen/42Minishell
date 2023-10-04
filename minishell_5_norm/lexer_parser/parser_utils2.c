/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdundar <fdundar@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:09:36 by fdundar           #+#    #+#             */
/*   Updated: 2023/10/04 14:09:36 by fdundar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	k = 1;
	while (temp_cmds[k])
		parser->cmds[i++] = ft_strdup(temp_cmds[k++]);
	set_exec(parser, env);
	free_split(temp_cmds);
	free_split(dollar);
}

void	set_heredoc(t_parser *parser, int i, int a)
{
	int		fd;
	char	*str;
	char	*eof;
	char	*file_name;

	file_name = set_filename(a);
	fd = open(file_name, O_CREAT | O_RDWR | O_APPEND , 0777);
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
