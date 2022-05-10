/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:59:37 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/09 22:05:49 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	get_command_index(const char *cmd)
{
	int	i;

	i = 0;
	while (i < NUM_COMMANDS && ft_strcmp(cmd, g_commands[i]) != 0)
		++i;
	return (i);
}

void	parse_commands(void)
{
}
