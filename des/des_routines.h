/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_routines.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 22:42:59 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/15 22:46:38 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_ROUTINES_H
# define DES_ROUTINES_H

# include "des.h"
# include "../utils/hex_str_to_int.h"
# include "../utils/swap_bytes.h"

void	init(uint64_t *data, t_des_processing_context *pr_ctx,
			t_des_context *ctx);

void	generate_sub_keys_parts(t_des_processing_context *pr_ctx);

void	generate_sub_keys(t_des_processing_context *pr_ctx);

void	encrypt_decrypt(t_des_processing_context *pr_ctx, t_des_context *ctx,
			int i);

void	calculate_apply_f(t_des_processing_context *pr_ctx);

#endif
