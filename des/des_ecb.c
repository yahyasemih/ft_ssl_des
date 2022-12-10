/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:26:25 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/18 20:20:54 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_ecb.h"
#include "des_routines.h"
#include "../base64/base64.h"

static void	ecb_process_block(t_des_context *ctx, uint64_t *data)
{
	t_des_processing_context	pr_ctx;
	int							i;

	init(data, &pr_ctx, ctx);
	generate_sub_keys_parts(&pr_ctx);
	generate_sub_keys(&pr_ctx);
	i = 0;
	while (i < 16)
	{
		encrypt_decrypt(&pr_ctx, ctx, i);
		calculate_apply_f(&pr_ctx);
		++i;
	}
	pr_ctx.pre_out = (((uint64_t)pr_ctx.r) << 32) | (uint64_t) pr_ctx.l;
	*data = 0;
	i = 0;
	while (i < 64)
	{
		*data <<= 1;
		*data |= (pr_ctx.pre_out >> (64 - g_rinit_permutation[i])) & 0x1;
		i++;
	}
}

static int	ecb_process_block_loop(t_des_context *ctx, char **res,
		uint64_t *block, int *total_len)
{
	char		buffer[9];
	int			r;
	int			old_r;

	r = 1;
	old_r = 1337;
	ft_memset(buffer, 0, 9);
	while (r > 0)
	{
		r = ft_read_block(ctx->input_fd, (char *)block, sizeof(uint64_t));
		if (old_r < 8 && r == 0 && ctx->mode == 'e')
			break ;
		old_r = padding_data(block, r);
		swap_bytes(block, sizeof(uint64_t));
		ecb_process_block(ctx, block);
		swap_bytes(block, sizeof(uint64_t));
		if ((int)((*block >> 56) & 0xffll) <= 8 && ctx->mode == 'd')
			old_r = 8 - (int)((*block >> 56) & 0xffll);
		*total_len += 8 * (ctx->mode == 'e') + old_r * (ctx->mode == 'd');
		*res = ft_strjoin(*res, ft_memcpy(buffer, block, 8), 8, 1);
		if (old_r < 8 && ctx->mode == 'd')
			break ;
	}
	return (r);
}

static int	ecb_process(t_des_context *ctx)
{
	int			r;
	uint64_t	block;
	char		*res;
	int			total_len;

	total_len = 0;
	res = NULL;
	//TODO: decode string before decrypt if -a option is provided
	r = ecb_process_block_loop(ctx, &res, &block, &total_len);
	if (ctx->is_base64 && ctx->mode == 'e')
	{
		res = encode_str(res);
		total_len = ((total_len / 3) + ((total_len / 3) % 3 != 0)) * 4 + 1;
	}
	write(ctx->output_fd, res, total_len);
	r = (r < 0 || res == NULL);
	if (res != NULL)
		free(res);
	return (r);
}

int	des_ecb(int argc, char *argv[])
{
	t_des_context	ctx;
	int				i;

	init_ctx(&ctx);
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
		{
			if (ft_strchr("iokspv", argv[i][1]) != NULL)
			{
				if (handle_option_param(&ctx, argv[i][1], argv[i + 1]))
					return (1);
				++i;
			}
			else if (ft_strchr("ade", argv[i][1]) != NULL)
				handle_options_with_no_param(&ctx, argv[i][1]);
			else
				return (invalid_option(argv[0], argv[i][1]));
		}
	}
	return (ecb_process(&ctx));
}
