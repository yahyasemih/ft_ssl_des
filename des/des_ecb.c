/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:26:25 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/12 23:43:40 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_ecb.h"

static int	encode_ecb(t_des_context *ctx)
{
	(void)ctx;
	return (0);
}

static int	decode_ecb(t_des_context *ctx)
{
	(void)ctx;
	return (0);
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
	if (ctx.mode == 'd')
		return (decode_ecb(&ctx));
	return (encode_ecb(&ctx));
}
