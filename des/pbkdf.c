/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 04:06:49 by yez-zain          #+#    #+#             */
/*   Updated: 2022/12/14 18:16:25 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "sha256/string_operations.h"
#include "utils/hex_str_to_int.h"
#include "utils/int_to_hex_str.h"
#include "utils/ft_strjoin.h"
#include "utils/get_password.h"

static char	*do_hmac(const char *inner_pad, const char *outer_pad,
		const char *message, size_t message_len)
{
	char	*str;
	char	*str2;

	str2 = ft_strjoin(inner_pad, message, (int)message_len, 0);
	str = sha256_from_string(str2, message_len + 64);
	free(str2);
	str2 = ft_strjoin(outer_pad, str, 32, 0);
	free(str);
	str = sha256_from_string(str2, 32 + 64);
	free(str2);
	return (str);
}

static char	*hmac_sha256(const char *password, size_t passwd_len,
		const char *message, size_t message_len)
{
	char	key[65];
	char	outer_pad[65];
	char	inner_pad[65];
	int		i;
	char	*str;

	ft_memset(key, 0, 65);
	ft_memset(inner_pad, 0, 65);
	ft_memset(outer_pad, 0, 65);
	if (passwd_len <= 64)
		ft_memcpy(key, password, passwd_len);
	else
	{
		str = sha256_from_string(password, passwd_len);
		ft_memcpy(key, str, 32);
		free(str);
	}
	i = 0;
	while (i < 64)
	{
		outer_pad[i] = (char)(key[i] ^ 0x5C);
		inner_pad[i] = (char)(key[i] ^ 0x36);
		++i;
	}
	return (do_hmac(inner_pad, outer_pad, message, message_len));
}

static void	generate_salt(t_des_context *ctx)
{
	int		fd;
	int		i;
	uint8_t	c;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return ;
	i = 0;
	while (i < 16)
	{
		if (read(fd, &c, 1) <= 0)
			return ;
		c = c % 16;
		if (c > 9)
			c = 'A' + (c - 10);
		else
			c = '0' + c;
		ctx->salt[i] = c;
		++i;
	}
	ctx->salt[i] = '\0';
	close(fd);
}

static void	derivation_process(t_des_context *ctx, uint64_t salt_data)
{
	char		*generated_key;
	char		*intermediate_key;
	char		final_salt[12];
	int			i;
	int			j;

	swap_bytes(&salt_data, sizeof(uint64_t));
	ft_memcpy(final_salt, &salt_data, sizeof(uint64_t));
	ft_memcpy(final_salt + sizeof(uint64_t), "\0\0\0\1", 4);
	generated_key = hmac_sha256(ctx->passwd, ft_strlen(ctx->passwd),
			final_salt, 12);
	ft_memcpy(ctx->key, generated_key, 16);
	i = 1;
	while (i < 10000)
	{
		intermediate_key = hmac_sha256(ctx->passwd, ft_strlen(ctx->passwd),
				generated_key, 32);
		j = 0;
		while (++j <= 16)
			ctx->key[j - 1] = (char)(ctx->key[j - 1] ^ intermediate_key[j - 1]);
		free(generated_key);
		generated_key = intermediate_key;
		++i;
	}
	free(generated_key);
}

void	make_key_from_password(t_des_context *ctx, const char *prompt)
{
	char		buff[17];
	uint64_t	data;

	if (!ctx->passwd[0] && get_password(prompt, ctx->passwd, _PASSWORD_LEN))
		return ;
	if (!ctx->salt[0])
		generate_salt(ctx);
	data = hex_str_to_int(ctx->salt, 16);
	derivation_process(ctx, data);
	ft_memcpy(&data, ctx->key, sizeof(uint64_t));
	int_to_hex_str(data, buff);
	ft_memcpy(&data, ctx->key + 8, sizeof(uint64_t));
	ft_memcpy(ctx->key, buff, 16);
	if (ctx->iv[0] != '\0')
	{
		data = hex_str_to_int(ctx->iv, (int)ft_strlen(ctx->iv));
		swap_bytes(&data, sizeof(uint64_t));
	}
	int_to_hex_str(data, buff);
	ft_memcpy(ctx->iv, buff, 16);
	if (write(1, "salt=", 5) && write(1, ctx->salt, 16) && write(1, "\nkey=", 5)
		&& write(1, ctx->key, 16) && write(1, "\niv =", 5)
		&& write(1, ctx->iv, 16))
		write(1, "\n", 1);
}
