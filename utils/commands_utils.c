/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 22:04:46 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/09 22:32:16 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands_utils.h"

int	invalid_option(const char *cmd, char o)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": invalid option -- ", 20);
	write(2, &o, 1);
	write(2, "\n", 1);
	return (1);
}

int	invalid_option_arg(const char *cmd, char o)
{
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
	return (1);
}
