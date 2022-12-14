/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_decode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:30:05 by yez-zain          #+#    #+#             */
/*   Updated: 2022/12/14 16:30:24 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_input_decode.h"

int	handle_input_decode(t_des_context *ctx)
{
	int		fd;
	char	*str;
	char	buff[1025];
	int		r;

	fd = open("/tmp/decode_data", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ctx->input_fd);
	while (1)
	{
		r = read(ctx->input_fd, buff, 1024);
		if (r <= 0)
			break ;
		buff[r] = '\0';
		if (r > 0 && buff[r - 1] == '\n')
			buff[r - 1] = '\0';
		str = decode_str(buff);
		write(fd, str, ft_strlen(str));
		free(str);
	}
	close(fd);
	r = ctx->input_fd;
	ctx->input_fd = open("/tmp/decode_data", O_RDONLY);
	return (r);
}
