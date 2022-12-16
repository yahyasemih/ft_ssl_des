/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:25:54 by yez-zain          #+#    #+#             */
/*   Updated: 2022/12/14 12:23:43 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_operations.h"
#include "state_operations.h"

char	*sha256_prepare_input_string(const char *str, uint64_t len)
{
	char		*s;
	int			r;
	int			new_len;
	uint64_t	bits_len;

	r = (int)len;
	new_len = ((((r + 8) / 64) + 1) * 64) - 8;
	s = malloc(new_len + 8);
	if (s == NULL)
		return (NULL);
	ft_memset(s, 0, new_len);
	ft_memcpy(s, str, r);
	s[r] = (char)128;
	bits_len = 8ULL * r;
	swap_bytes(&bits_len, sizeof(int64_t));
	ft_memcpy(s + new_len, &bits_len, sizeof(uint64_t));
	return (s);
}

void	sha256_print_result(uint32_t flags, const char *s, const char *src,
	int src_len)
{
	if (s == NULL)
		return ;
	else if ((flags & F_QUIET) != 0)
		write_in_hex(s, 32);
	else if ((flags & F_REVERSE) != 0)
	{
		write_in_hex(s, 32);
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
			write(1, "SHA256(", 7);
		write(1, "\"", (flags & F_IS_FILE) == 0);
		write(1, src, src_len);
		write(1, "\"", (flags & F_IS_FILE) == 0);
		write (1, ")= ", 3);
		write_in_hex(s, 32);
	}
	write(1, "\n", 1);
}

char	*sha256_fill_result(t_sha256_context *ctx, char *str,
	int hash_nbr)
{
	int		i;
	int		j;
	char	*s;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < hash_nbr)
	{
		j = 0;
		s = (char *)(ctx->big_h + i);
		while (j < 4)
		{
			str[i * 4 + j] = s[3 - j];
			++j;
		}
		++i;
	}
	str[hash_nbr * 4] = '\0';
	return (str);
}

static void	init_words_from_str(uint32_t *w, const char *str, int i)
{
	uint32_t	t;

	t = 0;
	while (t < 16)
	{
		w[t] = *(uint32_t *)(str + i + t * 4);
		swap_bytes(&w[t], sizeof(w[t]));
		++t;
	}
}

char	*sha256_from_string(const char *str, uint64_t len)
{
	t_sha256_context	ctx;
	uint32_t			i;
	uint32_t			t;
	char				*padded_str;

	sha256_init_ctx(&ctx);
	i = 0;
	padded_str = sha256_prepare_input_string(str, len);
	if (padded_str == NULL)
		return (NULL);
	while (i < len)
	{
		init_words_from_str(ctx.w, padded_str, (int)i);
		t = 16;
		while (t < 64)
		{
			ctx.w[t] = small_sigma_32(ctx.w[t - 2], 1) + ctx.w[t - 7]
				+ small_sigma_32(ctx.w[t - 15], 0) + ctx.w[t - 16];
			++t;
		}
		sha256_block_iteration(&ctx);
		i += 64;
	}
	free(padded_str);
	return (sha256_fill_result(&ctx, malloc(33 * sizeof(char)), 8));
}
