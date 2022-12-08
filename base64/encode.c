/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:45:49 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/15 14:20:57 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

static char	*encode_block(const unsigned char *block, int size)
{
	int		idx;
	char	*encoded;

	encoded = malloc(5 * sizeof(char));
	if (encoded == NULL)
		return (NULL);
	idx = block[0] >> 2;
	ft_memset(encoded, g_base[idx], 1);
	idx = (((block[0] << 6) & 0xFF) >> 2) + (block[1] >> 4);
	ft_memset(encoded + 1, g_base[idx], 1);
	if (size >= 2)
	{
		idx = (((block[1] << 4) & 0xF0) >> 2) + (((block[2] >> 6) & 0x0F));
		ft_memset(encoded + 2, g_base[idx], 1);
		idx = ((block[2] << 2) & 0xFF) >> 2;
		if (size >= 3)
			ft_memset(encoded + 3, g_base[idx], 1);
		else
			ft_memset(encoded + 3, '=', 1);
	}
	else
		ft_memset(encoded + 2, '=', 2);
	encoded[4] = '\0';
	return (encoded);
}

char	*encode(t_base64_context *ctx)
{
	int				r;
	unsigned char	buff[4];
	char			*res;
	char			*tmp;

	r = 1;
	res = NULL;
	while (r > 0)
	{
		r = ft_read_block(ctx->input_fd, (char *)buff, 3);
		if (r <= 0)
			break ;
		tmp = encode_block(buff, r);
		res = ft_strjoin(res, tmp, ft_strlen(tmp), 1);
		free(tmp);
		if (tmp == NULL)
			return (NULL);
	}
	if (r < 0)
	{
		free(res);
		return (NULL);
	}
	res = ft_strjoin(res, "\n", 1, 1);
	return (res);
}

char	*encode_str(const char *str)
{
	int		i;
	char	*res;
	char	*tmp;
	int		len;

	len = ft_strlen(str);
	res = NULL;
	i = 0;
	while (i < len)
	{
		if (len - i >= 3)
			tmp = encode_block((const unsigned char *)str + i, 3);
		else
			tmp = encode_block((const unsigned char *)str + i, len - i);
		res = ft_strjoin(res, tmp, ft_strlen(tmp), 1);
		free(tmp);
		if (tmp == NULL)
			return (NULL);
		i += 3;
	}
	free((char *)str);
	res = ft_strjoin(res, "\n", 1, 1);
	return (res);
}
