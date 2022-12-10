/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_str_to_int.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 22:10:31 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/15 22:11:01 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEX_STR_TO_INT_H
# define HEX_STR_TO_INT_H

# include <stdint.h>
# include <stdlib.h>

uint64_t	hex_str_to_int(const char *str, int len);

#endif
