/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:20:15 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 16:20:40 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state_operations.h"

uint32_t	ch_32(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ ((~x) & z));
}

uint32_t	maj_32(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t	rotr_32(uint32_t x, uint32_t n)
{
	return ((x >> n) | (x << (32 - n)));
}

uint32_t	big_sigma_32(uint32_t x, int i)
{
	if (i == 0)
		return (rotr_32(x, 2) ^ rotr_32(x, 13) ^ rotr_32(x, 22));
	else
		return (rotr_32(x, 6) ^ rotr_32(x, 11) ^ rotr_32(x, 25));
}

uint32_t	small_sigma_32(uint32_t x, int i)
{
	if (i == 0)
		return (rotr_32(x, 7) ^ rotr_32(x, 18) ^ (x >> 3));
	else
		return (rotr_32(x, 17) ^ rotr_32(x, 19) ^ (x >> 10));
}
