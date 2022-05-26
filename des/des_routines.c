/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_routines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 22:42:20 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/16 11:22:37 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_routines.h"

void	init(uint64_t *data, t_des_processing_context *pr_ctx,
	t_des_context *ctx)
{
	int	i;

	ft_memset(pr_ctx, 0, sizeof(t_des_processing_context));
	pr_ctx->m = 0;
	i = 0;
	while (i < 64)
	{
		pr_ctx->m <<= 1;
		pr_ctx->m |= (*data >> (64 - g_init_permutation[i])) & 0x1;
		++i;
	}
	pr_ctx->l = (uint32_t)(pr_ctx->m >> 32) & 0x00000000ffffffff;
	pr_ctx->r = (uint32_t)pr_ctx->m & 0x00000000ffffffff;
	pr_ctx->k = hex_str_to_int(ctx->key, ft_strlen(ctx->key));
	pr_ctx->kp = 0;
	i = 0;
	while (i < 56)
	{
		pr_ctx->kp <<= 1;
		pr_ctx->kp |= (pr_ctx->k >> (64 - g_permuted_choice_1[i])) & 0x1;
		++i;
	}
}

void	generate_sub_keys_parts(t_des_processing_context *pr_ctx)
{
	int			i;
	int			j;

	pr_ctx->c[0] = (uint32_t)((pr_ctx->kp >> 28) & 0x000000000FFFFFFF);
	pr_ctx->d[0] = (uint32_t)((pr_ctx->kp & 0x000000000FFFFFFF));
	i = 1;
	while (i < 17)
	{
		pr_ctx->c[i] = pr_ctx->c[i - 1];
		pr_ctx->d[i] = pr_ctx->d[i - 1];
		j = 0;
		while (j < g_iteration_shift[i - 1])
		{
			pr_ctx->c[i] = (0x0fffffff & (pr_ctx->c[i] << 1))
				| (0x1 & (pr_ctx->c[i] >> 27));
			pr_ctx->d[i] = (0x0fffffff & (pr_ctx->d[i] << 1))
				| (0x1 & (pr_ctx->d[i] >> 27));
			j++;
		}
		++i;
	}
}

void	generate_sub_keys(t_des_processing_context *pr_ctx)
{
	int			i;
	int			j;
	uint64_t	tmp;

	i = 0;
	while (i < 16)
	{
		tmp = ((uint64_t)pr_ctx->d[i + 1])
			| (((uint64_t)pr_ctx->c[i + 1]) << 28);
		j = 0;
		pr_ctx->kn[i] = 0;
		while (j < 48)
		{
			pr_ctx->kn[i] <<= 1;
			pr_ctx->kn[i] |= (tmp >> (56 - g_permuted_choice_2[j])) & 0x1;
			++j;
		}
		++i;
	}
}

void	encrypt_decrypt(t_des_processing_context *pr_ctx, t_des_context *ctx,
	int i)
{
	int			j;

	j = 0;
	while (j < 48)
	{
		pr_ctx->expanded <<= 1;
		pr_ctx->expanded |= (uint64_t)((pr_ctx->r >> (32 - g_expand[j])) & 0x1);
		j++;
	}
	if (ctx->mode == 'd')
		pr_ctx->expanded = pr_ctx->expanded ^ pr_ctx->kn[15 - i];
	else
		pr_ctx->expanded = pr_ctx->expanded ^ pr_ctx->kn[i];
	j = -1;
	while (++j < 8)
	{
		pr_ctx->row = (char)((pr_ctx->expanded & (0x840000000000 >> (6 * j)))
				>> (42 - 6 * j));
		pr_ctx->row = (pr_ctx->row >> 4) | (pr_ctx->row & 0x01);
		pr_ctx->cl = (char)((pr_ctx->expanded & (0x780000000000 >> (6 * j)))
				>> (43 - 6 * j));
		pr_ctx->output <<= 4;
		pr_ctx->output |= (uint32_t)(g_sbox[j][16 * pr_ctx->row
				+ pr_ctx->cl] & 0x0f);
	}
}

void	calculate_apply_f(t_des_processing_context *pr_ctx)
{
	int			j;
	uint64_t	tmp;

	pr_ctx->f = 0;
	j = 0;
	while (j < 32)
	{
		pr_ctx->f <<= 1;
		pr_ctx->f |= (pr_ctx->output >> (32 - g_post_sbox_permutation[j]))
			& 0x1;
		j++;
	}
	tmp = pr_ctx->r;
	pr_ctx->r = pr_ctx->l ^ pr_ctx->f;
	pr_ctx->l = tmp;
}
