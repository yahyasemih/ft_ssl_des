/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:31:42 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 16:32:01 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block_operations.h"

void	sha256_update_ctx(t_sha256_context *ctx, int update_hash)
{
	if (update_hash == 1)
	{
		ctx->big_h[0] += ctx->a;
		ctx->big_h[1] += ctx->b;
		ctx->big_h[2] += ctx->c;
		ctx->big_h[3] += ctx->d;
		ctx->big_h[4] += ctx->e;
		ctx->big_h[5] += ctx->f;
		ctx->big_h[6] += ctx->g;
		ctx->big_h[7] += ctx->h;
	}
	else
	{
		ctx->a = ctx->big_h[0];
		ctx->b = ctx->big_h[1];
		ctx->c = ctx->big_h[2];
		ctx->d = ctx->big_h[3];
		ctx->e = ctx->big_h[4];
		ctx->f = ctx->big_h[5];
		ctx->g = ctx->big_h[6];
		ctx->h = ctx->big_h[7];
	}
}

void	sha256_block_iteration(t_sha256_context *ctx)
{
	uint32_t	t;

	sha256_update_ctx(ctx, 0);
	t = 0;
	while (t < 64)
	{
		ctx->t1 = ctx->h + big_sigma_32(ctx->e, 1)
			+ ch_32(ctx->e, ctx->f, ctx->g) + g_sha256_k[t] + ctx->w[t];
		ctx->t2 = big_sigma_32(ctx->a, 0) + maj_32(ctx->a, ctx->b, ctx->c);
		ctx->h = ctx->g;
		ctx->g = ctx->f;
		ctx->f = ctx->e;
		ctx->e = ctx->d + ctx->t1;
		ctx->d = ctx->c;
		ctx->c = ctx->b;
		ctx->b = ctx->a;
		ctx->a = ctx->t1 + ctx->t2;
		++t;
	}
	sha256_update_ctx(ctx, 1);
}

void	sha256_process_block(const uint32_t *bloc, t_sha256_context *ctx)
{
	uint32_t	t;

	t = 0;
	while (t < 16)
	{
		ctx->w[t] = bloc[t];
		swap_bytes(&ctx->w[t], sizeof(ctx->w[t]));
		++t;
	}
	while (t < 64)
	{
		ctx->w[t] = small_sigma_32(ctx->w[t - 2], 1) + ctx->w[t - 7]
			+ small_sigma_32(ctx->w[t - 15], 0) + ctx->w[t - 16];
		++t;
	}
	sha256_block_iteration(ctx);
}

void	sha256_init_ctx(t_sha256_context *ctx)
{
	ctx->big_h[0] = 0x6a09e667;
	ctx->big_h[1] = 0xbb67ae85;
	ctx->big_h[2] = 0x3c6ef372;
	ctx->big_h[3] = 0xa54ff53a;
	ctx->big_h[4] = 0x510e527f;
	ctx->big_h[5] = 0x9b05688c;
	ctx->big_h[6] = 0x1f83d9ab;
	ctx->big_h[7] = 0x5be0cd19;
}
