/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_operations.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:19:49 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 16:24:59 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_OPERATIONS_H
# define STATE_OPERATIONS_H

# include "sha256.h"

uint32_t	ch_32(uint32_t x, uint32_t y, uint32_t z);

uint32_t	maj_32(uint32_t x, uint32_t y, uint32_t z);

uint32_t	rotr_32(uint32_t x, uint32_t n);

uint32_t	big_sigma_32(uint32_t x, int i);

uint32_t	small_sigma_32(uint32_t x, int i);

#endif
