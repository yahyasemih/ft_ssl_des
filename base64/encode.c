/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:45:49 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/10 20:22:16 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

static void	encode_block(t_base64_context *ctx, const char *block, int size)
{
	int		idx;

	idx = block[0] >> 2;
	write(ctx->output_fd, g_base + idx, 1);
	idx = (((block[0] << 6) & 0xFF) >> 2) + (block[1] >> 4);
	write(ctx->output_fd, g_base + idx, 1);
	if (size >= 2)
	{
		idx = (((block[1] << 4) & 0xF0) >> 2) + (((block[2] >> 6) & 0x0F));
		write(ctx->output_fd, g_base + idx, 1);
		idx = ((block[2] << 2) & 0xFF) >> 2;
		if (size >= 3)
			write(ctx->output_fd, g_base + idx, 1);
		else
			write(ctx->output_fd, "=", 1);
	}
	else
		write(ctx->output_fd, "==", 2);
}

int	encode(t_base64_context *ctx)
{
	int		r;
	char	buff[4];

	r = 1;
	while (r > 0)
	{
		r = ft_read_block(ctx->input_fd, buff, 3);
		if (r <= 0)
			break ;
		encode_block(ctx, buff, r);
	}
	write(ctx->output_fd, "\n", 1);
	return (r < 0);
}
