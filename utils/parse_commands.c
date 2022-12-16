/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:02:03 by yez-zain          #+#    #+#             */
/*   Updated: 2022/12/14 15:43:36 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include "ft_ssl.h"

static int	arg_count(const char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && ft_strchr("\t\v\f ", line[i]) != NULL)
			++i;
		if (line[i] == '\0')
			break ;
		++count;
		if (line[i] == '"')
			while (line[++i] != '"')
				;
		else if (line[i] == '\'')
			while (line[++i] != '\'')
				;
		else
			while (line[i] != '\0' && ft_strchr("\t\v\f ", line[i]) == NULL)
				++i;
		if (line[i] != '\0')
			++i;
	}
	return (count);
}

static char	*process_arg(const char *line, int i, const char *end)
{
	int		len;
	char	*s;

	len = 0;
	while (line[i + len] != '\0' && ft_strchr(end, line[i + len]) == NULL)
		++len;
	if (ft_strchr(end, '"') != NULL || ft_strchr(end, '\'') != NULL)
	{
		if (line[i + len] == '\0')
			return (NULL);
	}
	s = malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	ft_memcpy(s, line + i, len);
	s[len] = '\0';
	return (s);
}

static int	handle_strings(const char *line, int *i, int *j, char **argv)
{
	int	old_j;

	old_j = *j;
	if (line[*i] != '\0')
	{
		if (line[*i] == '"' || line[*i] == '\'')
		{
			if (line[*i] == '"')
				argv[(*j)++] = process_arg(line, ++(*i), "\"");
			else if (line[*i] == '\'')
				argv[(*j)++] = process_arg(line, ++(*i), "'");
			if (argv[old_j] != NULL)
				*i += (int)ft_strlen(argv[old_j]) + 1;
			else
				return (1);
		}
		else
			argv[(*j)++] = process_arg(line, *i, "\t\v\f ");
		while (line[*i] != '\0' && ft_strchr("\t\v\f ", line[*i]) == NULL)
			++(*i);
	}
	if (old_j != *j && argv[old_j] == NULL)
		return (1);
	else
		return (0);
}

static char	**split_command(const char *line)
{
	int		argc;
	char	**argv;
	int		i;
	int		j;

	argc = arg_count(line);
	argv = malloc(sizeof(char *) * (argc + 1));
	if (ft_memset(argv, 0, sizeof(char *) * (argc + 1)) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && ft_strchr("\t\v\f ", line[i]) != NULL)
			++i;
		if (line[i] == '\0')
			break ;
		if (handle_strings(line, &i, &j, argv))
		{
			return (free_args(argc, argv), NULL);
		}
		if (line[i] != '\0')
			++i;
	}
	return (argv);
}

void	parse_commands(void)
{
	char	*line;
	char	**argv;
	int		argc;

	while (1)
	{
		line = readline("ft_ssl> ");
		if (line == NULL)
			return ;
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		argc = arg_count(line);
		argv = split_command(line);
		if (argv != NULL)
			g_command_functions[get_command_index(argv[0])](argc, argv);
		else
			write(2, "ft_ssl: invalid input\n", 22);
		free_args(argc, argv);
		free(line);
	}
}
