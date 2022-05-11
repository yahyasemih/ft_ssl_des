/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:59:09 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 15:59:10 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap_bytes.h"

void	swap_bytes(void *x, uint32_t size)
{
	char		s[16];
	char		c;
	uint32_t	i;

	i = 0;
	ft_memcpy(s, x, size);
	while (i < size / 2)
	{
		c = s[i];
		s[i] = s[size - 1 - i];
		s[size - 1 - i] = c;
		++i;
	}
	ft_memcpy(x, s, size);
}
