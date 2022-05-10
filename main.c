/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:21:08 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/09 21:18:49 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	main(int argc, char *argv[])
{
	t_command_function	command;

	if (argc <= 1)
	{
		parse_commands();
	}
	else
	{
		command = g_command_functions[get_command_index(argv[1])];
		return (command(argc - 1, argv + 1));
	}
	return (0);
}
