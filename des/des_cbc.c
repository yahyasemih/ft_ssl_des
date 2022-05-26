/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:26:25 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/18 20:20:48 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_cbc.h"
#include "des_routines.h"
#include "../base64/base64.h"

static void	cbc_process_block(t_des_context *ctx, uint64_t *data)
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

static int	padding_data(uint64_t *data, int len)
{
	int	i;

	if (len == 8)
		return (8);
	i = len;
	while (i < 8)
	{
		ft_memset(((char *)data) + i, 8 - len, 1);
		++i;
	}
	return (len);
}

static int	cbc_process(t_des_context *ctx)
{
	int			r;
	int			old_r;
	uint64_t	block;
	char		*res;
	char		tmp[9];
	uint64_t	prev;
	uint64_t	curr;
	int			total_len;

	r = 1;
	total_len = 0;
	old_r = 1337;
	res = NULL;
	ft_memset(tmp, 0, 9);
	prev = hex_str_to_int(ctx->iv, ft_strlen(ctx->iv));
	while (r > 0)
	{
		r = ft_read_block(ctx->input_fd, (char *)&block, sizeof(uint64_t));
		if (old_r < 8 && r == 0)
			break ;
		old_r = padding_data(&block, r);
		swap_bytes(&block, sizeof(uint64_t));
		if (ctx->mode == 'e')
		{
			block ^= prev;
			cbc_process_block(ctx, &block);
			prev = block;
		}
		else
		{
			curr = block;
			cbc_process_block(ctx, &block);
			block ^= prev;
			prev = curr;
		}
		swap_bytes(&block, 8);
		res = ft_strjoin(res, ft_memcpy(tmp, &block, sizeof(uint64_t)), 1);
		total_len += 8;
	}
	if (ctx->is_base64 && ctx->mode == 'e')
		res = encode_str(res);
	write(ctx->output_fd, res, total_len);
	return (r < 0 || res == NULL);
}

int	des_cbc(int argc, char *argv[])
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
	return (cbc_process(&ctx));
}
