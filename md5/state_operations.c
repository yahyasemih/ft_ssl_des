/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:24:32 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 14:29:01 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state_operations.h"

void	do_f(t_md5_context *ctx, uint32_t i)
{
	ctx->f = (ctx->b & ctx->c) | ((~ctx->b) & ctx->d);
	ctx->g = i;
}

void	do_g(t_md5_context *ctx, uint32_t i)
{
	ctx->f = (ctx->d & ctx->b) | ((~ctx->d) & ctx->c);
	ctx->g = (5 * i + 1) % 16;
}

void	do_h(t_md5_context *ctx, uint32_t i)
{
	ctx->f = ctx->b ^ ctx->c ^ ctx->d;
	ctx->g = (3 * i + 5) % 16;
}

void	do_i(t_md5_context *ctx, uint32_t i)
{
	ctx->f = ctx->c ^ (ctx->b | (~ctx->d));
	ctx->g = (7 * i) % 16;
}

void	rotate_states(uint32_t *bloc, uint32_t i, t_md5_context *ctx)
{
	uint32_t	tmp;
	uint32_t	left_rotate;
	uint32_t	a;

	tmp = ctx->d;
	ctx->d = ctx->c;
	ctx->c = ctx->b;
	a = ctx->a + ctx->f + g_k[i] + bloc[ctx->g];
	left_rotate = ((a << g_r[i]) | (a >> (32 - g_r[i])));
	ctx->b += left_rotate;
	ctx->a = tmp;
}
