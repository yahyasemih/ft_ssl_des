/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:59:37 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 19:39:11 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	get_command_index(const char *cmd)
{
	int	i;
	int	size;

	size = sizeof(g_commands) / sizeof(const char *);
	if (cmd == NULL)
		return (size);
	i = 0;
	while (i < size && ft_strcmp(cmd, g_commands[i]) != 0)
		++i;
	return (i);
}
