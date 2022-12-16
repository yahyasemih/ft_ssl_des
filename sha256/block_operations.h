/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_operations.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:29:53 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 16:32:55 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_OPERATIONS_H
# define BLOCK_OPERATIONS_H

# include "state_operations.h"

void	sha256_update_ctx(t_sha256_context *ctx, int update_hash);

void	sha256_process_block(const uint32_t *bloc, t_sha256_context *ctx);

#endif
