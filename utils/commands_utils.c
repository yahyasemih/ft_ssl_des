/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:04:46 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/15 00:48:50 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands_utils.h"

int	invalid_option(const char *cmd, char o)
{
	write(2, "ft_ssl: ", 8);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": invalid option -- ", 20);
	write(2, &o, 1);
	write(2, "\n", 1);
	return (1);
}

int	invalid_option_arg(const char *cmd, char o)
{
	write(2, "ft_ssl: ", 8);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": option requires an argument -- ", 33);
	write(2, &o, 1);
	write(2, "\n", 1);
	return (1);
}

int	invalid_command(int argc, char *argv[])
{
	(void)argc;
	write(2, "ft_ssl: Error: '", 16);
	write(2, argv[0], ft_strlen(argv[0]));
	write(2, "' is an invalid command.\n", 25);
	write(2, "\nStandard commands:\n", 20);
	write(2, "\nMessage Digest commands:\n", 26);
	write(2, "md5\n", 4);
	write(2, "sha256\n", 7);
	write(2, "\nCipher commands:\n", 18);
	write(2, "base64\n", 7);
	write(2, "des\n", 4);
	write(2, "des-ecb\n", 8);
	write(2, "des-cbc\n", 8);
	return (1);
}

int	invalid_file(const char *cmd, const char *file)
{
	write(2, "ft_ssl: ", 8);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	perror("");
	return (1);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
