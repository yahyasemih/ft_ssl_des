/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_hex_str.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:36:30 by yez-zain          #+#    #+#             */
/*   Updated: 2022/12/14 13:47:10 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_TO_HEX_STR_H
# define INT_TO_HEX_STR_H

# include <stdint.h>

void	int_to_hex_str(uint64_t data, char *dst);

#endif