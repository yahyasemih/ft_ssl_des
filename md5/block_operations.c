/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:51:19 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 16:52:05 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "block_operations.h"
#include "state_operations.h"

void	process_block(uint32_t *bloc, t_md5_context *ctx)
{
	uint32_t	i;

	ctx->a = ctx->h[0];
	ctx->b = ctx->h[1];
	ctx->c = ctx->h[2];
	ctx->d = ctx->h[3];
	i = 0;
	while (i < 64)
	{
		if (i <= 15)
			do_f(ctx, i);
		else if (i <= 31)
			do_g(ctx, i);
		else if (i <= 47)
			do_h(ctx, i);
		else
			do_i(ctx, i);
		rotate_states(bloc, i, ctx);
		++i;
	}
	ctx->h[0] += ctx->a;
	ctx->h[1] += ctx->b;
	ctx->h[2] += ctx->c;
	ctx->h[3] += ctx->d;
}
