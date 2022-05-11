/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 21:20:35 by yez-zain          #+#    #+#             */
/*   Updated: 2022/05/11 16:52:18 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "block_operations.h"
#include "state_operations.h"
#include "string_operations.h"

static char	*last_stream_block(t_md5_context *ctx, char *buff, int r,
	uint64_t total_len)
{
	char		*s;
	uint32_t	new_len;
	uint64_t	bits_len;

	buff[r] = (char)128;
	bits_len = 8ULL * total_len;
	new_len = ((((r + 8) / 64) + 1) * 64) - 8;
	ft_memcpy(buff + new_len, &bits_len, sizeof(uint64_t));
	process_block((uint32_t *)(buff), ctx);
	if (new_len + 8 > 64)
		process_block((uint32_t *)(buff + 64), ctx);
	s = malloc(17 * sizeof(char));
	if (s == NULL)
		return (NULL);
	return (fill_result(ctx, s));
}

static char	*md5_from_stream(int fd)
{
	char			buff[128];
	uint32_t		r;
	t_md5_context	ctx;
	uint64_t		total_len;

	r = 1;
	total_len = 0;
	ctx.h[0] = 0x67452301;
	ctx.h[1] = 0xEFCDAB89;
	ctx.h[2] = 0x98BADCFE;
	ctx.h[3] = 0x10325476;
	while (r > 0)
	{
		r = ft_read_block(fd, buff, 64);
		if (r < 0)
			return (NULL);
		ft_memset(buff + r, 0, 128 - r);
		total_len += r;
		if (fd == 0)
			write(1, buff, r);
		if (r < 64)
			break ;
		process_block((uint32_t *)(buff), &ctx);
	}
	return (last_stream_block(&ctx, buff, r, total_len));
}

static int	handle_options(int argc, char *argv[], int i, uint32_t *flags)
{
	char	*s;

	s = NULL;
	if (argv[i][1] == 's' && i + 1 >= argc)
		return (argc + invalid_option_arg(argv[0], 's'));
	if (argv[i][1] == 'r')
		*flags |= F_REVERSE;
	else if (argv[i][1] == 'q')
		*flags |= F_QUIET;
	else if (argv[i][1] == 'p')
	{
		s = md5_from_stream(0);
		md5_print_result(F_QUIET, s, "", 0);
	}
	else if (argv[i][1] == 's')
	{
		s = md5_from_string(argv[i + 1], ft_strlen(argv[i + 1]));
		md5_print_result(*flags, s, argv[i + 1], ft_strlen(argv[i + 1]));
		++i;
	}
	else
		return (argc + invalid_option(argv[0], argv[i][1]));
	free(s);
	return (i);
}

static int	handle_files(char *argv[], int i, uint32_t flags)
{
	int		fd;
	int		return_value;
	char	*s;

	return_value = 0;
	fd = open(argv[i], O_RDONLY);
	if (fd >= 0)
	{
		s = md5_from_stream(fd);
		md5_print_result(flags | F_IS_FILE, s, argv[i], ft_strlen(argv[i]));
		free(s);
	}
	else
		return_value = invalid_file(argv[0], argv[i]);
	close(fd);
	return (return_value);
}

int	md5(int argc, char *argv[])
{
	int			i;
	int			fd;
	uint32_t	flags;
	int			return_value;

	i = 0;
	flags = 0;
	fd = INT32_MAX;
	return_value = 0;
	while (++i < argc)
	{
		if (fd == INT32_MAX && argv[i][0] == '-')
			i = handle_options(argc, argv, i, &flags);
		else
			return_value = handle_files(argv, i, flags);
	}
	return (i > argc || return_value > 0);
}
