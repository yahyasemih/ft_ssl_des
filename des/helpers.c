/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:37:26 by yez-zain          #+#    #+#             */
/*   Updated: 2022/12/14 14:16:14 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

int	open_files(t_des_context *ctx, char mode, const char *file)
{
	if (file == NULL)
		return (invalid_option_arg("des-ecb", mode));
	else if (file[0] == '-' && file[1] == '\0')
		return (0);
	else if (mode == 'i')
	{
		ctx->input_fd = open(file, O_RDONLY);
		if (ctx->input_fd < 0)
			write(2, "des-ecb: Error: unable to open input file: ", 43);
	}
	else
	{
		ctx->output_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ctx->output_fd < 0)
			write(2, "des-ecb: Error: unable to open output file: ", 44);
	}
	if (ctx->input_fd < 0 || ctx->output_fd < 0)
	{
		write(2, file, ft_strlen(file));
		write(2, "\n", 1);
	}
	return (ctx->input_fd < 0 || ctx->output_fd < 0);
}

void	init_ctx(t_des_context *ctx)
{
	ctx->mode = 'e';
	ctx->input_fd = 0;
	ctx->output_fd = 1;
	ctx->is_base64 = 0;
	ft_memset(&ctx->key, 0, 17);
	ft_memset(&ctx->iv, 0, 17);
	ft_memset(&ctx->salt, 0, 17);
	ft_memset(&ctx->passwd, 0, _PASSWORD_LEN + 1);
}

int	handle_option_param(t_des_context *ctx, char opt, const char *arg)
{
	if (arg == NULL)
		return (invalid_option_arg("des-ecb", opt));
	else if ((opt == 'i' || opt == 'o'))
	{
		if (open_files(ctx, opt, arg))
			return (1);
	}
	else if (opt == 'k')
		ft_memcpy(&ctx->key, arg, min((int)ft_strlen(arg) + 1, 16));
	else if (opt == 's')
		ft_memcpy(&ctx->salt, arg, min((int)ft_strlen(arg) + 1, 16));
	else if (opt == 'p')
		ft_memcpy(&ctx->passwd, arg, min((int)ft_strlen(arg) + 1,
				_PASSWORD_LEN));
	else if (opt == 'v')
		ft_memcpy(&ctx->iv, arg, min((int)ft_strlen(arg) + 1, 16));
	return (0);
}

void	handle_options_with_no_param(t_des_context *ctx, char opt)
{
	if (opt == 'e' || opt == 'd')
		ctx->mode = opt;
	else if (opt == 'a')
		ctx->is_base64 = 1;
}

int	padding_data(uint64_t *data, int len)
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
