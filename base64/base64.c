/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:29:03 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/14 22:17:48 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

static int	open_files(t_base64_context *ctx, char mode, char *file)
{
	if (file == NULL)
		return (invalid_option_arg("base64", mode));
	else if (file[0] == '-' && file[1] == '\0')
		return (0);
	else if (mode == 'i')
	{
		ctx->input_fd = open(file, O_RDONLY);
		if (ctx->input_fd < 0)
			write(2, "base64: Error: unable to open input file: ", 42);
	}
	else
	{
		ctx->output_fd = open(file, O_WRONLY | O_CREAT, 0644);
		if (ctx->output_fd < 0)
			write(2, "base64: Error: unable to open output file: ", 43);
	}
	if (ctx->input_fd < 0 || ctx->output_fd < 0)
	{
		write(2, file, ft_strlen(file));
		write(2, "\n", 1);
	}
	return (ctx->input_fd < 0 || ctx->output_fd < 0);
}

static void	init_ctx(t_base64_context *ctx)
{
	ctx->input_fd = 0;
	ctx->output_fd = 1;
	ctx->mode = 'e';
}

static int	do_work(t_base64_context *ctx)
{
	char	*res;

	if (ctx->mode == 'd')
		res = decode(ctx);
	else
		res = encode(ctx);
	if (res == NULL)
		return (1);
	write(ctx->output_fd, res, ft_strlen(res));
	return (0);
}

int	base64(int argc, char *argv[])
{
	t_base64_context	ctx;
	int					i;

	init_ctx(&ctx);
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
		{
			if ((argv[i][1] == 'i' || argv[i][1] == 'o'))
			{
				if (open_files(&ctx, argv[i][1], argv[i + 1]))
					return (1);
				++i;
			}
			else if (argv[i][1] == 'e' || argv[i][1] == 'd')
				ctx.mode = argv[i][1];
			else
				return (invalid_option(argv[0], argv[i][1]));
		}
	}
	return (do_work(&ctx));
}
