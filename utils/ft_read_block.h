/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_block.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:39:41 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/10 20:13:48 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READ_BLOCK_H
# define FT_READ_BLOCK_H

# include <unistd.h>
# include "libc_utils.h"

int	ft_read_block(int fd, char *block_buff, int bock_size);

#endif
