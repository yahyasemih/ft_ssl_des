/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:28:47 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 14:49:39 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_operations.h"

char	*fill_result(t_md5_context *ctx, char *str)
{
	int		i;
	int		j;
	char	*s;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		j = 0;
		s = (char *)(ctx->h + i);
		while (j < 4)
		{
			str[i * 4 + j] = s[j];
			++j;
		}
		++i;
	}
	str[16] = '\0';
	return (str);
}

char	*prepare_input_string(const char *str)
{
	char		*s;
	int			r;
	int			new_len;
	uint64_t	bits_len;

	r = ft_strlen(str);
	new_len = ((((r + 8) / 64) + 1) * 64) - 8;
	s = malloc(new_len + 8);
	if (s == NULL)
		return (NULL);
	ft_memset(s, 0, new_len);
	ft_memcpy(s, str, r);
	s[r] = (char)128;
	bits_len = 8ULL * r;
	ft_memcpy(s + new_len, &bits_len, sizeof(uint64_t));
	return (s);
}

void	write_in_hex(const char *str, int len)
{
	int		i;
	char	c;
	char	*hex;

	i = 0;
	hex = "0123456789abcdef";
	while (i < len)
	{
		c = hex[(str[i] & 0xF0) >> 4];
		write(1, &c, 1);
		c = hex[str[i] & 0x0F];
		write(1, &c, 1);
		++i;
	}
}

void	print_result(uint32_t flags, const char *s, const char *src,
	int src_len)
{
	if (s == NULL)
		return ;
	else if ((flags & F_QUIET) != 0)
		write_in_hex(s, 16);
	else if ((flags & F_REVERSE) != 0)
	{
		write_in_hex(s, 16);
		write(1, " \"", 1 + ((flags & F_IS_FILE) == 0));
		write(1, src, src_len);
		write(1, "\"", (flags & F_IS_FILE) == 0);
	}
	else
	{
		if ((flags & F_IS_FILE) && (flags & F_IS_STDIN)
			&& ft_strcmp(src, "stdin") == 0)
			write(1, "(", 1);
		else
			write(1, "MD5 (", 5);
		write(1, "\"", (flags & F_IS_FILE) == 0);
		write(1, src, src_len);
		write(1, "\"", (flags & F_IS_FILE) == 0);
		write (1, ") = ", 4);
		write_in_hex(s, 16);
	}
	write(1, "\n", 1);
}

char	*md5_from_string(const char *str, uint64_t len)
{
	t_md5_context	ctx;
	uint32_t		offset;
	char			*s;
	char			*padded_str;

	ctx.h[0] = 0x67452301;
	ctx.h[1] = 0xEFCDAB89;
	ctx.h[2] = 0x98BADCFE;
	ctx.h[3] = 0x10325476;
	offset = 0;
	padded_str = prepare_input_string(str);
	if (padded_str == NULL)
		return (NULL);
	while (offset < len)
	{
		process_block((uint32_t *)(padded_str + offset), &ctx);
		offset += 64;
	}
	s = malloc(17 * sizeof(char));
	if (s == NULL)
	{
		free(padded_str);
		return (NULL);
	}
	return (fill_result(&ctx, s));
}
