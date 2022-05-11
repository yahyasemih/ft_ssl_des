/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_operations.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:49:21 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 16:51:32 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_OPERATIONS_H
# define BLOCK_OPERATIONS_H

# include "md5.h"

void	process_block(uint32_t *bloc, t_md5_context *ctx);

#endif