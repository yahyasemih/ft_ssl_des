/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_in_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:11:39 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 16:12:32 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "write_in_hex.h"

void	write_in_hex(const char *str, int len)
{
	int		i;
	char	c;
	char	*hex;

	i = 0;
	hex = "0123456789abcdef";
	while (i < len)
	{
		c = hex[(str[i] & 0xF0) >> 4];
		write(1, &c, 1);
		c = hex[str[i] & 0x0F];
		write(1, &c, 1);
		++i;
	}
}
