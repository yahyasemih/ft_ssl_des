/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_operations.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:25:00 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 14:28:14 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_OPERATIONS_H
# define STATE_OPERATIONS_H

# include "md5.h"

void	do_f(t_md5_context *ctx, uint32_t i);

void	do_g(t_md5_context *ctx, uint32_t i);

void	do_h(t_md5_context *ctx, uint32_t i);

void	do_i(t_md5_context *ctx, uint32_t i);

void	rotate_states(uint32_t *bloc, uint32_t i, t_md5_context *ctx);

#endif
