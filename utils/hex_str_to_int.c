/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_str_to_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 22:09:56 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/15 22:12:18 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hex_str_to_int.h"

uint64_t	hex_str_to_int(const char *str, int len)
{
	uint64_t	r;
	int			i;

	if (str == NULL)
		return (0);
	r = 0;
	i = 0;
	while (i < len && i < 16)
	{
		r <<= 4;
		if (str[i] >= '0' && str[i] <= '9')
			r |= (str[i] - '0');
		else if (str[i] >= 'A' && str[i] <= 'F')
			r |= (str[i] - 'A') + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			r |= (str[i] - 'a') + 10;
		++i;
	}
	r <<= (4 * (16 - i));
	return (r);
}
