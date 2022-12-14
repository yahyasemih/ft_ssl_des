/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:25:46 by yez-zain          #+#    #+#             */
/*   Updated: 2022/12/14 15:43:36 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_ECB_H
# define DES_ECB_H

# include "des.h"
# include "utils/ft_read_block.h"
# include "utils/ft_strjoin.h"
# include "utils/hex_str_to_int.h"
# include "utils/swap_bytes.h"

int	des_ecb(int argc, char *argv[]);

#endif
