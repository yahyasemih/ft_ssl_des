/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:47:34 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/15 00:49:19 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

static int	read_valid_block(int fd, char *block_buff, int block_size)
{
	int		r;
	int		total_r;
	char	c;

	ft_memset(block_buff, 0, block_size);
	total_r = 0;
	r = 1;
	while (r > 0)
	{
		c = '\0';
		r = read(fd, &c, 1);
		if (r < 0)
			return (-1);
		if (ft_strchr(g_base, c) == NULL && c != '=')
			continue ;
		block_buff[total_r] = c;
		total_r += r;
		block_buff[total_r] = '\0';
		if (total_r == block_size)
			break ;
	}
	return (total_r);
}

static int	get_complement_number(const char *buff, int size)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (i < size)
	{
		if (buff[i] == '=')
			++nb;
		++i;
	}
	if (nb > 2)
		return (2);
	else
		return (nb);
}

static uint32_t	get_decoded_data(const char *buff)
{
	uint32_t	data;
	int			i;
	char		c;

	data = 0;
	i = 0;
	while (i < 4)
	{
		if ((buff[0] == '=' || buff[1] == '='
				|| (ft_strchr(g_base, buff[i]) == NULL
					&& ft_strchr("\t\n\v\f\r ", buff[i]) == NULL
					&& buff[i] != '=')))
			return (-write(2, "Invalid character in input stream.\n", 35));
		c = 0;
		while (c < 64 && g_base[c - 0] != buff[i])
			++c;
		if (c > 0 && c < 64)
			data |= c;
		if (i < 3)
			data <<= 6;
		++i;
	}
	return (data);
}

char	*decode(t_base64_context *ctx)
{
	char		buff[5];
	uint32_t	data;
	int			i;
	char		*res;
	char		tmp[4];

	res = NULL;
	while (read_valid_block(ctx->input_fd, buff, 4) > 0)
	{
		data = get_decoded_data(buff);
		if (data < 0)
		{
			free(res);
			return (NULL);
		}
		i = 2;
		while (i >= get_complement_number(buff, 4))
		{
			ft_memset(tmp + (2 - i), ((char *)&data)[i], 1);
			i--;
		}
		tmp[2 - i] = '\0';
		res = ft_strjoin(res, tmp, ft_strlen(tmp), 1);
	}
	return (res);
}
