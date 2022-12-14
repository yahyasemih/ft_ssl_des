/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:26:25 by yez-zain          #+#    #+#             */
/*   Updated: 2022/12/14 16:31:08 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_cbc.h"
#include "des_routines.h"
#include "base64/base64.h"
#include "utils/handle_input_decode.h"

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

static void	cbc_encode_decode_block(t_des_context *ctx, uint64_t *block,
		uint64_t *prev, uint64_t *curr)
{
	swap_bytes(block, sizeof(uint64_t));
	if (ctx->mode == 'e')
	{
		*block ^= *prev;
		cbc_process_block(ctx, block);
		*prev = *block;
	}
	else
	{
		*curr = *block;
		cbc_process_block(ctx, block);
		*block ^= *prev;
		*prev = *curr;
	}
	swap_bytes(block, sizeof(uint64_t));
}

static int	cbc_process_loop(t_des_context *ctx, char **res, uint64_t *block,
		int *total_len)
{
	int			r;
	int			old_r;
	char		buffer[9];
	uint64_t	prev;
	uint64_t	curr;

	r = 1;
	ft_memset(buffer, 0, 9);
	old_r = 1337;
	prev = hex_str_to_int(ctx->iv, (int)ft_strlen(ctx->iv));
	while (r > 0)
	{
		r = ft_read_block(ctx->input_fd, (char *)block, sizeof(uint64_t));
		if (old_r < 8 && r == 0 && ctx->mode == 'e')
			break ;
		old_r = padding_data(block, r);
		cbc_encode_decode_block(ctx, block, &prev, &curr);
		if ((int)((*block >> 56) & 0xffll) <= 8 && ctx->mode == 'd')
			old_r = 8 - (int)((*block >> 56) & 0xffll);
		*res = ft_strjoin(*res, ft_memcpy(buffer, block, 8), 8, 1);
		*total_len += 8 * (ctx->mode == 'e') + old_r * (ctx->mode == 'd');
		if (old_r < 8 && ctx->mode == 'd')
			break ;
	}
	return (r);
}

static int	cbc_process(t_des_context *ctx)
{
	int			r;
	char		*res;
	int			total_len;
	uint64_t	block;
	int			fd;

	if (ctx->key[0] == '\0')
		return (1);
	total_len = 0;
	res = ft_strjoin("", "", 0, 0);
	if (ctx->mode == 'd' && ctx->is_base64)
		fd = handle_input_decode(ctx);
	r = cbc_process_loop(ctx, &res, &block, &total_len);
	if (ctx->is_base64 && ctx->mode == 'e')
	{
		res = encode_str(res);
		total_len = ((total_len / 3) + ((total_len / 3) % 3 != 0)) * 4 + 1;
	}
	write(ctx->output_fd, res, total_len);
	r = (r < 0 || res == NULL);
	if (res != NULL)
		free(res);
	if (ctx->mode == 'd' && ctx->is_base64)
		ctx->input_fd = fd;
	return (r);
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
	if (ctx.key[0] == '\0')
		make_key_from_password(&ctx, "enter DES-CBC encryption password:");
	return (cbc_process(&ctx));
}
